/* Copyright (C) 2022
 * All rights reserved.
 *
 * Projet Sac
 * Ecole du Web
 * Cours Objets connectés (c)2022
 *  
    @file     main.cpp
    @author   Samuel GASSAMA
    @version  1.0 17/11/2022

    Historique des versions
           Version      Date            Auteur           Description
           1.0        17/11/2022    Samuel GASSAMA       Première version du logiciel
           1.0        17/11/2022    Samuel GASSAMA       Première version du logiciel


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

// --------------Ajout des classes Oled---------------
#include "MyOledViewWifiAp.h"
#include "MyOledViewInitialisation.h"
#include "MyOledViewWorkingOFF.h"
#include "MyOledViewWorkingCOLD.h"
#include "MyOledViewWorkingHEAT.h"

MyOledViewWifiAp *myOledViewWifiAp = NULL;
MyOledViewInitialisation *myOledViewInitialisation = NULL;
MyOledViewWorkingOFF *myOledViewWorkingOFF = NULL;
MyOledViewWorkingCOLD *myOledViewWorkingCOLD = NULL;
MyOledViewWorkingHEAT *myOledViewWorkingHEAT = NULL;

// --------------Gestion des LEDS---------------
 #define GPIO_PIN_LED_YELLOW 12
 #define GPIO_PIN_LED_GREEN  14
 #define GPIO_PIN_LED_RED    27

// --------------Gestion du serveur WEB---------------
#include "WiFi.h"

const char* ssid = "ESP32-Soft-accessPoint";
const char* password = "microcontrollerslab";
WiFiServer server(80);

// --------------Gestion du Senseur de Température---------------
#include "TemperatureStub.h"
#define DHTPIN  15   // Pin utilisée par le senseur DHT11 / DHT22
#define DHTTYPE DHT22  //Le type de senseur utilisé (mais ce serait mieux d'avoir des DHT22 pour plus de précision)
TemperatureStub *temperatureStub = NULL;
float  temperature = temperatureStub->getTemperature();
int currentTemperatureDisplayed = 0;
char strTemperature[128];
float temperatureActuelle = 0.0;

#define nomSysteme "SAC System" 
string idDuSysteme = "1337";

// ------------------ Gestion boutons ----------------------
#include <MyButton.h>
#include "MyButton.h"
MyButton *myButtonAction = NULL;
MyButton *myButtonReset = NULL;

// ---------------------- Bool sur le fonctionnement du four ---------------------------------------
boolean demarre = false; // permet de savoir si le Four est en marche
bool redLedIsOn = false;
bool greenLedIsOn = false;
bool yellowLedIsOn = false;
string status = "Off"; // permet a l'esp et au site de savoir quel est le status du four
int timer = 0; // permet de gérer le délais dans la fonction loop

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
std::string CallBackMessageListener(string message)
{
    while (replaceAll(message, std::string("  "), std::string(" ")));
    // Décortiquer le message
    string arg1 = getValue(message, ' ', 1);
    string arg2 = getValue(message, ' ', 2);
    string arg3 = getValue(message, ' ', 3);
    string actionToDo = getValue(message, ' ', 0);

    float temperature = temperatureStub->getTemperature();
    String temp = (String)temperature;
    if (string(actionToDo.c_str()).compare(string("temperature")) == 0)
    {
        return (temp.c_str());
    }

    std::string nomDuFour = "Four #1";
    if (string(actionToDo.c_str()).compare(string("askNomFour")) == 0)
    {
        return(nomDuFour.c_str());
    }

    // fonctions qui renvois le statut actuel du four ( off, cold, heat)
    if (string(actionToDo.c_str()).compare(string("askStatus")) == 0)
    {
        return (status.c_str());
    }

    if (string(actionToDo.c_str()).compare(string("action")) == 0)
    {
        return (String("Ok").c_str());
    }

    // ---------------------- Set le status du four  ---------------------------------
    if (string(actionToDo.c_str()).compare(string("setEtatFour")) == 0)
    {
        status = arg1;
        return (String("Ok").c_str());           
    }

    std::string result = "";
    return result;
}

// ---------------------- Fonction pour l'affichage du status du four sur le OLED ---------------------------------
void displayStateOled()
{
    delay(10);
    sprintf(strTemperature, "%g", temperature);

    if (status == "Off")
    {
        myOledViewWorkingOFF = new MyOledViewWorkingOFF();
        myOledViewWorkingOFF->setParams("nomDuSysteme", nomSysteme);
        myOledViewWorkingOFF->setParams("idDuSysteme", idDuSysteme);
        myOledViewWorkingOFF->setParams("temperature", strTemperature);
        myOledViewWorkingOFF->setParams("ipDuSysteme", WiFi.localIP().toString().c_str());
        myOled->displayView(myOledViewWorkingOFF);
        currentTemperatureDisplayed = temperature;
        Serial.println("Display State OFF");
    }

    if (status == "Cold")
    {
        myOledViewWorkingCOLD = new MyOledViewWorkingCOLD();
        myOledViewWorkingCOLD->setParams("nomDuSysteme", nomSysteme);
        myOledViewWorkingCOLD->setParams("idDuSysteme", idDuSysteme.c_str());
        myOledViewWorkingCOLD->setParams("temperature", strTemperature);
        myOledViewWorkingCOLD->setParams("ipDuSysteme", WiFi.localIP().toString().c_str());
        myOled->displayView(myOledViewWorkingCOLD);
        currentTemperatureDisplayed = temperature;
        Serial.println("Display State COLD");
    }

    if(status == "Heat")
    {
        myOledViewWorkingHEAT = new MyOledViewWorkingHEAT();
        myOledViewWorkingHEAT->setParams("nomDuSysteme", nomSysteme);
        myOledViewWorkingHEAT->setParams("idDuSysteme", idDuSysteme);
        myOledViewWorkingHEAT->setParams("temperature", strTemperature);
        myOledViewWorkingHEAT->setParams("ipDuSysteme", WiFi.localIP().toString().c_str());
        myOled->displayView(myOledViewWorkingHEAT);
        currentTemperatureDisplayed = temperature;
        Serial.println("Display State HEAT");
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


    if (!wm.autoConnect(ssIDRandom.c_str(), PASSRandom.c_str()))
    {
        Serial.println("Erreur de connexion.");
    }
    else 
    {
        Serial.println("Connexion Établie:");
        delay(1000);
    }
        
    myOledViewWifiAp->setNomDuSysteme("SAC System");
    myOledViewWifiAp->setSsIDDuSysteme(ssIDRandom.c_str());
    myOledViewWifiAp->setPassDuSysteme(PASSRandom.c_str());

    myOled->displayView(myOledViewWifiAp);

    // ----------- Initialisation des LED statuts ----------------
    pinMode(GPIO_PIN_LED_YELLOW, OUTPUT);
    pinMode(GPIO_PIN_LED_GREEN, OUTPUT);
    pinMode(GPIO_PIN_LED_RED , OUTPUT);

    // ----------- Clignotement des led au démarrage du système----------------
    for (int i = 0; i < 2; i++)
    {
        digitalWrite(GPIO_PIN_LED_RED,HIGH);
        digitalWrite(GPIO_PIN_LED_GREEN,HIGH);
        digitalWrite(GPIO_PIN_LED_YELLOW,HIGH);
        delay(1000);
        digitalWrite(GPIO_PIN_LED_RED,LOW);
        digitalWrite(GPIO_PIN_LED_GREEN,LOW);
        digitalWrite(GPIO_PIN_LED_YELLOW,LOW);
        delay(1000);
    }

    digitalWrite(GPIO_PIN_LED_RED,HIGH);
    digitalWrite(GPIO_PIN_LED_GREEN,HIGH);
    digitalWrite(GPIO_PIN_LED_YELLOW,HIGH);

    // ----------- Routes du serveur ----------------
    myServer = new MyServer(80);
    myServer->initAllRoutes();
    myServer->initCallback(&CallBackMessageListener);

    // ----------- Senseur de température ----------------
    temperatureStub = new TemperatureStub();
    temperatureStub->init(DHTPIN, DHTTYPE);
}
 
void loop()
{
    if (timer % 1000 == 0)
    {
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

        if (status == "Off" && !redLedIsOn)
        {
            redLedIsOn = true;
            yellowLedIsOn = false;
            greenLedIsOn = false;
            digitalWrite(GPIO_PIN_LED_GREEN, LOW);
            digitalWrite(GPIO_PIN_LED_YELLOW, LOW);
            digitalWrite(GPIO_PIN_LED_RED, HIGH);
            displayStateOled();
        }
        if (status == "Heat" && !yellowLedIsOn)
        {
            yellowLedIsOn = true;
            redLedIsOn = false;
            greenLedIsOn = false;
            digitalWrite(GPIO_PIN_LED_GREEN, LOW);
            digitalWrite(GPIO_PIN_LED_YELLOW, HIGH);
            digitalWrite(GPIO_PIN_LED_RED, LOW);
            displayStateOled();
        }
        if (status == "Cold" && !greenLedIsOn)
        {
            greenLedIsOn = true;
            yellowLedIsOn = false;
            redLedIsOn = false;
            digitalWrite(GPIO_PIN_LED_GREEN, HIGH);
            digitalWrite(GPIO_PIN_LED_YELLOW, LOW);
            digitalWrite(GPIO_PIN_LED_RED, LOW);
            displayStateOled();
        }

        Serial.println("Passage dans le loop");
        Serial.println("Status actuel : " + String(status.c_str()));
    }
    timer += 10;
    delay(10);
