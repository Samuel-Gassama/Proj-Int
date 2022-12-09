/* Copyright (C) 2022
 * All rights reserved.
 *
 * Projet Sac
 * Ecole du Web
 * Cours Objets connectés (c)2022
 *  
    @file     main.cpp
    @author   David Tremblay
    @version  1.0 17/11/2022

    Historique des versions
           Version      Date            Auteur           Description
           1.0        17/11/2022    David Tremblay       Première version du logiciel

    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
                      
            ESPAsyncWebServer-esphome                   (Pour accéder au Wifi)
            AsyncTCP-esphome                            (Pour utiliser les focntionnalités TCP)
            bblanchon/ArduinoJson@^6.17.2               (Pour accéder au fonctionnalités Json)

    Autres librairies (à copier dans le répertoire lib)
         WifiManagerDevelopment
            //Remarques
            //Pour trouver le WifiManager (dans la branche development)
            //   https://github.com/tzapu/WiFiManager/tree/development
            //   Ne pas oublier d'appuyez sur l'ampoule et choisir : ajouter Lib
    
    Fonctions utiles (utilitaires)
        /lib/MYLIB/myFunctions.cpp
            //Pour vérifier plus simplement que deux chaines sont identiques
            bool isEqualString(std::string line1, std::string line2)
            //Pour extraire une partie d'une chaine de caractères avec l'aide d'un index
            std::string getValue(std::string data, char separator, int index)
            //Pour remplacer plus facilement une sous chaine
            bool replaceAll(std::string& source, const std::string& from, const std::string& to)
            //Pour obtenir un chaine aléatoire d'une certaine longeur
            std::string get_random_string(unsigned int len)

    Classes du système
         
        MyServer                        V1.0    Pour la gestion des routes pour le site WEB
            /data                               Répertoire qui contient les fichiers du site WEB 
                index.html              V1.0    Page index du site WEB
                index.css               V1.0    CSS
                script.js               V1.0    JS (fonctions JavaScript)

     Arborescence des classes systèmes
            /lib/
                Mylib/
                    MyServer             V1.0    Pour la gestion des routes pour le site WEB
                    myFunctions          V1.0    Fonctions utilitaires pour le projet
                MYOLED/
                    MyOled.cpp              V1.1    Gestion d'un écran Oled Utilisant un GPIO d'un contrôleur
                    MyOledView              V1.1    Gestion d'une VUE pour le OLed  
                    MyOledViewErrorWifiConnexion     V1.2
                    MyOledViewInitialisation         V1.2
                    MyOledViewWifiAp                 V1.2
                    MyOledViewWorking
                    MyOledViewWorkingOff
                    MyOledViewWorkingCold
                    MyOledViewWorkingHeat
            /src
                main.cpp             V1.0   Code principal
                MyButton.cpp         V1.0   Gestion d'un bouton pour permettre au système de démarrer
                TemperatureStub.cpp  V1.0   Gestion de la température du Four (STUB)

              
 * */

#include <iostream>
#include <string>

#include <Arduino.h>
#include <ArduinoJson.h>

#include "myFunctions.cpp" //fonctions utilitaires
using namespace std;

#include <HTTPClient.h>
#include <WiFiManager.h>
WiFiManager wm;
#define WEBSERVER_H


#include <Wire.h>
#include <MyOled.h>
#include <MyOledView.h>

#include "MyOledViewWifiAp.h"
MyOledViewWifiAp *myOledViewWifiAp = NULL;

#include "MyOledViewInitialisation.h"
MyOledViewInitialisation *myOledViewInitialisation = NULL;

#include "MyOledViewWorkingOFF.h"
MyOledViewWorkingOFF *myOledViewWorkingOFF = NULL;

#include "MyOledViewWorkingCOLD.h"
MyOledViewWorkingCOLD *myOledViewWorkingCOLD = NULL;

#include "MyOledViewWorkingHEAT.h"
MyOledViewWorkingHEAT *myOledViewWorkingHEAT = NULL;


#include <MyButton.h>

// --------------Gestion des LEDS---------------

 #define GPIO_PIN_LED_HEAT_BLEU 2
 #define GPIO_PIN_LED_HEAT_VERT 0
 #define GPIO_PIN_LED_HEAT_ROUGE 18

#include "WiFi.h"

const char* ssid = "ESP32-Soft-accessPoint";
const char* password = "microcontrollerslab";
WiFiServer server(80);

#include "TemperatureStub.h"
#define DHTPIN  15   // Pin utilisée par le senseur DHT11 / DHT22
#define DHTTYPE DHT22  //Le type de senseur utilisé (mais ce serait mieux d'avoir des DHT22 pour plus de précision)
TemperatureStub *temperatureStub = NULL;
float temperature;
int currentTemperatureDisplayed = 0;
char strTemperature[128];
float temperatureActuelle = 0.0;
string etatFour = "null";

#define nomSysteme "SAC System" 
string idDuSysteme = "1337";

// ------------------ Gestion boutons ----------------------

#include "MyButton.h"
MyButton *myButtonAction = NULL;
MyButton *myButtonReset = NULL;

// ---------------------- Bool sur le fonctionnement du four ---------------------------------------

// permet de savoir si le Four est en marche
boolean demarre = false;
string status = "null";// permet à la page web de savoir quel est le status de l'esp




// ------------------- Valeur envoyées par le service WEB ------------------------------------------

string duree = "null";
float temperatureFloat;
int dureeInt;
// ------------------- Pour l'affichage OLED  ------------------------------------------

MyOled *myOled = NULL;
#define SCREEN_WIDTH 128      // taille de l'écran en longeur, en pixel
#define SCREEN_HEIGHT 64      // taille de l'écran en largeur, en pixel
#define OLED_RESET 4          // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_I2C_ADDRESS 0x3C // Adresse I2C de l'écran Oled
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int frame_delay = 15;



//------------------------ Serveur ESP32 -----------------------------

#include "MyServer.h"
MyServer *myServer = NULL;

//------------------------- Constance pour la connection Wifi ---------

const char *SSID = "SAC_";
const char *PASSWORD = "sac_";
String ssIDRandom;

//fonction statique qui permet aux objets d'envoyer des messages (callBack) 
//  arg0 : Action 
// arg1 ... : Parametres

std::string CallBackMessageListener(string message) {
    while(replaceAll(message, std::string("  "), std::string(" ")));
    //Décortiquer le message
    string arg1 = getValue(message, ' ', 0);
    float temperature = temperatureStub->getTemperature();
    String temp = (String)temperature;
    if(string(arg1.c_str()).compare(string("temperature")) == 0){
    return (temp.c_str());
    }

    string arg2 = getValue(message, ' ', 2);
    string arg3 = getValue(message, ' ', 3);
    string arg4 = getValue(message, ' ', 4);
    string arg5 = getValue(message, ' ', 5);

    string actionToDo = getValue(message, ' ', 0);
    std::string nomDuFour = "Four9394";
     if(string(actionToDo.c_str()).compare(string("askNomFour")) == 0) {
    return(temp.c_str()); }

    // fonctions qui renvois le statut actuel du four ( off, cold, heat)
    if (string(actionToDo.c_str()).compare(string("askStatus")) == 0)
    {
        return (status.c_str());
    }

    if (string(actionToDo.c_str()).compare(string("action")) == 0)
    {
        return (String("Ok").c_str());
    }

    std::string result = "";
    return result;

// ---------------------- Renvoi le status du four  ---------------------------------

  if (string(actionToDo.c_str()).compare(string("setEtatFour")) == 0)
    {
      etatFour = arg1;               //On convertit le string en float
    }

std::string result = "";
return result;
}
// ---------------------- Fonction pour l'affichage du status du four sur le OLED ---------------------------------

void displayStateOled(){
  delay(10);
  sprintf(strTemperature, "%g", temperature);
  if(isEqualString(status.c_str(), string("HEAT"))) myOled->updateCurrentView(myOledViewWorkingHEAT);
  if(isEqualString(status.c_str(), string("DONE"))) {
    myOledViewWorkingOFF = new MyOledViewWorkingOFF();
    myOledViewWorkingOFF->setParams("nomDuSysteme", nomSysteme);
    myOledViewWorkingOFF->setParams("idDuSysteme", idDuSysteme);
    myOledViewWorkingOFF->setParams("temperature", strTemperature);
    myOledViewWorkingOFF->setParams("ipDuSysteme",WiFi.localIP().toString().c_str());
    myOled->displayView(myOledViewWorkingOFF);
    currentTemperatureDisplayed = temperature;
  }

  if(isEqualString(status.c_str(), string("COLD"))) {
    myOledViewWorkingCOLD = new MyOledViewWorkingCOLD();
    myOledViewWorkingCOLD->setParams("nomDuSysteme", nomSysteme);
    myOledViewWorkingCOLD->setParams("idDuSysteme", idDuSysteme.c_str());
    myOledViewWorkingCOLD->setParams("temperature", strTemperature);
    myOledViewWorkingCOLD->setParams("ipDuSysteme",WiFi.localIP().toString().c_str());
    myOled->displayView(myOledViewWorkingCOLD);
    currentTemperatureDisplayed = temperature;
  }

  if(isEqualString(status.c_str(), string("HEAT"))) {
    myOledViewWorkingHEAT = new MyOledViewWorkingHEAT();
    myOledViewWorkingHEAT->setParams("nomDuSysteme", nomSysteme);
    myOledViewWorkingHEAT->setParams("idDuSysteme", idDuSysteme);
    myOledViewWorkingHEAT->setParams("temperature", strTemperature);
    myOledViewWorkingHEAT->setParams("ipDuSysteme",WiFi.localIP().toString().c_str());
    myOled->displayView(myOledViewWorkingHEAT);
    currentTemperatureDisplayed = temperature;
  }
} 

void Connect_WiFi()
{
    WiFi.begin(ssid, password);
    while(WiFi.status() != WL_CONNECTED)
    {
        delay(100); 
    }
}


void setup()
{ 
   Serial.begin(9600);
    delay(100);

   myOled = new MyOled(&Wire, OLED_RESET, SCREEN_HEIGHT, SCREEN_WIDTH);
   myOled->init(OLED_I2C_ADDRESS, true);

   myOledViewWifiAp = new MyOledViewWifiAp();
   myOledViewInitialisation = new MyOledViewInitialisation();

    myOledViewInitialisation->setNomDuSysteme("SAC System");
    myOledViewInitialisation->setIdDuSysteme("1234");
    myOledViewInitialisation->setSensibiliteBoutonAction("????");
    myOledViewInitialisation->setSensibiliteBoutonReset("????");

    myOled->displayView(myOledViewInitialisation);


   // ------------------ Gestion boutons ----------------------

    myButtonAction = new MyButton();        //Pour lire le bouton actions
    myButtonAction->init(T8);
    int sensibilisationButtonAction = myButtonAction->autoSensibilisation();

    myButtonReset = new MyButton();         //Pour lire le bouton hard reset
    myButtonReset->init(T9);
    int sensibilisationButtonReset = myButtonReset->autoSensibilisation();

   Serial.print("sensibilisationButtonAction : "); Serial.println(sensibilisationButtonAction);
   Serial.print("sensibilisationButtonReset : "); Serial.println(sensibilisationButtonReset);

    myOledViewInitialisation->setSensibiliteBoutonAction(String(sensibilisationButtonAction).c_str());
    myOledViewInitialisation->setSensibiliteBoutonReset(String(sensibilisationButtonReset).c_str());

    myOled->displayView(myOledViewInitialisation);

   
// ------------------- Gestion du Wifi Manager ------------------------------------------

    String ssIDRandom, PASSRandom;
    String stringRandom;
    stringRandom = get_random_string(4).c_str();
    ssIDRandom = SSID;
    ssIDRandom = ssIDRandom + stringRandom;
    stringRandom = get_random_string(4).c_str();
    PASSRandom = PASSWORD;
    PASSRandom = PASSRandom + stringRandom;

char strToPrint[128];
    sprintf(strToPrint, "Identification : %s   MotDePasse: %s", ssIDRandom, PASSRandom);
    Serial.println(strToPrint);


 if (!wm.autoConnect(ssIDRandom.c_str(), PASSRandom.c_str())){
        Serial.println("Erreur de connexion.");
      
        }
    else 
    {
        Serial.println("Connexion Établie:");
        delay(1000);
    };
        
    //  myOled->clearDisplay();

    myOledViewWifiAp->setNomDuSysteme("SAC System");
    myOledViewWifiAp->setSsIDDuSysteme(ssIDRandom.c_str());
    myOledViewWifiAp->setPassDuSysteme(PASSRandom.c_str());

     myOled->displayView(myOledViewWifiAp);

    // ----------- Initialisation des LED statuts ----------------

    pinMode(GPIO_PIN_LED_HEAT_BLEU, OUTPUT);
    pinMode(GPIO_PIN_LED_HEAT_ROUGE, OUTPUT);
    pinMode(GPIO_PIN_LED_HEAT_VERT , OUTPUT);

// ----------- Clignotement des led au démarrage du système----------------

    for(int i = 0; i < 2; i++){
    digitalWrite(GPIO_PIN_LED_HEAT_ROUGE,HIGH);
    digitalWrite(GPIO_PIN_LED_HEAT_VERT,HIGH);
    digitalWrite(GPIO_PIN_LED_HEAT_BLEU,HIGH);
    delay(1000);
    digitalWrite(GPIO_PIN_LED_HEAT_ROUGE,LOW);
    digitalWrite(GPIO_PIN_LED_HEAT_VERT,LOW);
    digitalWrite(GPIO_PIN_LED_HEAT_BLEU,LOW);
    delay(1000);
    }

    digitalWrite(GPIO_PIN_LED_HEAT_ROUGE,HIGH);
    digitalWrite(GPIO_PIN_LED_HEAT_VERT,HIGH);
    digitalWrite(GPIO_PIN_LED_HEAT_BLEU,HIGH);


    // ----------- Routes du serveur ----------------

    myServer = new MyServer(80);
    myServer->initAllRoutes();
    myServer->initCallback(&CallBackMessageListener);

    // ----------- Senseur de température ----------------

    temperatureStub = new TemperatureStub();
    temperatureStub->init(DHTPIN, DHTTYPE);
    
    
 }

void loop() {

// -----------Gestion du bouton Action-----------

    int buttonAction = myButtonAction->checkMyButton();
    if (buttonAction > 1)
    { // Si appuyé plus de 0.1 secondes
        Serial.println("action");
    }

    // -----------Gestion du bouton Reset-----------
    int buttonReset = myButtonReset->checkMyButton();
    if (buttonReset > 2)
    { // Si appuyé plus de 0.1 secondes
        Serial.println("reset");
        ESP.restart();
    }
// ----------- Gestion du display, température-----------

    float temperatureTMP = temperatureStub->getTemperature();

    
    delay(1000);


    // if (!demarre)
    // {
    //     status = "off";

    //     digitalWrite(GPIO_PIN_LED_HEAT_VERT, LOW);
    //     digitalWrite(GPIO_PIN_LED_HEAT_ROUGE, LOW);
    //     digitalWrite(GPIO_PIN_LED_HEAT_BLEU, LOW);
    //     digitalWrite(GPIO_PIN_LED_HEAT_VERT, HIGH);
    //     delay(70);
    // }
    // else
    // {
    //     //si le four est lancé, on verifie la temperature
    //     if (temperatureTMP < temperatureFloat)
    //     {
    //         status = "cold";
    //           digitalWrite(GPIO_PIN_LED_HEAT_ROUGE, LOW);
    //           digitalWrite(GPIO_PIN_LED_HEAT_ROUGE, LOW);
    //           digitalWrite(GPIO_PIN_LED_HEAT_BLEU, LOW);
    //           digitalWrite(GPIO_PIN_LED_HEAT_VERT, HIGH);
    //     }
    //     else
    //     {
    //         //si la temperature est bonne, on declenche une boucle qui se termine à la fin du timer (ou si la temperature a trop baissée)
    //         status = "heat";
    //         int timer = dureeInt + 1;
    //         do
    //         {
    //             timer = timer - 1;
    //             Serial.print(timer);

    //             digitalWrite(GPIO_PIN_LED_HEAT_VERT, LOW);
    //             digitalWrite(GPIO_PIN_LED_HEAT_ROUGE, LOW);
    //             digitalWrite(GPIO_PIN_LED_HEAT_BLEU, LOW);
    //             digitalWrite(GPIO_PIN_LED_HEAT_VERT, HIGH);
    //             delay(1000);

    //         } while (temperatureTMP >= temperatureFloat && timer > 0);
    //         // quand le chauffage est terminé, le four doit s'arreter
    //         demarre = false;
    //     }

  }

    // delay(1000);
// }