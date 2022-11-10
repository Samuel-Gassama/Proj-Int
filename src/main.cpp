/* Copyright (C) 2021 Alain Dube
 * All rights reserved.
 *
 * Projet Sac
 * Ecole du Web
 * Cours Objets connectés (c)2021
 *  
    @file     main.cpp
    @author   Alain Dubé
    @version  1.1 21/08/15 

    Historique des versions
           Version    Date       Auteur       Description
           1.0        21/08/15  Alain       Première version du logiciel
           1.1        22/09/7   Samuel     Version 1.1 du logiciel
           1.2       22/09/21   DavidT      Version 1.2 du logiciel
           1.3        22/10/3   Samuel      Version 1.3 du logiciel
           1.4        22/10/10  Samuel      Version 1.4 du logiciel

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
              
 * */

#include <iostream>
#include <cstring>

#include <Arduino.h>
#include <ArduinoJson.h>

#include "myFunctions.cpp" //fonctions utilitaires
#include "MyOled/MyOled.h"

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_NeoPixel.h"
#include <Wire.h>
// #include "MyOledView.h" //Fonction Oled
// #include "MyOledViewInitialisation.h"
// #include "MyOledViewWifiAp.h"

#define Protocole I2C, Adresse : 0x3C (défaut)
#define GPIO21 : SDA
#define GPIO22 : SCL
#define OLED_I2C_ADDRESS 0x3C // Adresse I2C de l'écran Oled

// Definition des dimensions de l'écran OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4

// MyOled *myOled = NULL;
// MyOledViewInitialisation *viewIni = NULL;

// MyOledViewWorkingWifiAp *viewWifi = NULL;

#include <HTTPClient.h>
#include <WiFiManager.h>
WiFiManager wm;
#define WEBSERVER_H

// Include de la classe MyButton.h

// #include "MyButton.h"
// MyButton *myButtonAction = NULL;
// MyButton *myButtonReset = NULL;

//Pour la gestion du serveur ESP32
#include "MyServer.h"
MyServer *myServer = NULL;

//Variable pour la connection Wifi
const char *SSID = "SAC_";
const char *PASSWORD = "sac_";
String ssIDRandom;

// Include de la classe du sensor, définition des pins utilisés par le sensor 

#include "TemperatureStub.h"
#define DHTPIN  15   // Pin utilisée par le senseur DHT11 / DHT22
#define DHTTYPE DHT22  //Le type de senseur utilisé (mais ce serait mieux d'avoir des DHT22 pour plus de précision)
TemperatureStub *temperatureStub = NULL;

//Définition des trois leds de statut
#define GPIO_PIN_LED_LOCK_ROUGE         12 //GPIO12
#define GPIO_PIN_LED_OK_GREEN             14 //GPIO14
#define GPIO_PIN_LED_HEAT_YELLOW        27 //GPIO27

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
    string arg6 = getValue(message, ' ', 6);
    string arg7 = getValue(message, ' ', 7);
    string arg8 = getValue(message, ' ', 8);
    string arg9 = getValue(message, ' ', 9);
    string arg10 = getValue(message, ' ', 10);

   
    string actionToDo = getValue(message, ' ', 0);
    std::string nomDuFour = "Four9394";
     if(string(actionToDo.c_str()).compare(string("askNomFour")) == 0) {
    return(temp.c_str()); }
    

std::string result = "";
return result;
}



void setup() { 
    Serial.begin(9600);
    delay(100);

// Affichage sur le OLED du MyOledInitialisation

//    myOled = new MyOled(&Wire, OLED_RESET, SCREEN_HEIGHT, SCREEN_WIDTH);
//    myOled->init(OLED_I2C_ADDRESS, true);
//    viewIni = new MyOledViewInitialisation();


//     viewIni->setNomDuSysteme("SAC System");
//     viewIni->setIdDuSysteme("1234");
//     viewIni->setSensibiliteBoutonAction("????");
//     viewIni->setSensibiliteBoutonReset("????");

//     myOled->displayView(viewIni);


   //Gestion des boutons
//     myButtonAction = new MyButton();        //Pour lire le bouton actions
//     myButtonAction->init(T8);
//     int sensibilisationButtonAction = myButtonAction->autoSensibilisation();

//     myButtonReset = new MyButton();         //Pour lire le bouton hard reset
//     myButtonReset->init(T9);
//     int sensibilisationButtonReset = myButtonReset->autoSensibilisation();

//    Serial.print("sensibilisationButtonAction : "); Serial.println(sensibilisationButtonAction);
//    Serial.print("sensibilisationButtonReset : "); Serial.println(sensibilisationButtonReset);

//     viewIni->setSensibiliteBoutonAction(String(sensibilisationButtonAction).c_str());
//     viewIni->setSensibiliteBoutonReset(String(sensibilisationButtonReset).c_str());

//     myOled->displayView(viewIni);// Affichage de la vue viewIni


 //Connection au WifiManager
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
    else {
        Serial.println("Connexion Établie.");
        }


    // ----------- Routes du serveur ----------------
    myServer = new MyServer(80);
    myServer->initAllRoutes();
    myServer->initCallback(&CallBackMessageListener);

    //Initiation pour la lecture de la température
    temperatureStub = new TemperatureStub;
    temperatureStub->init(DHTPIN, DHTTYPE); //Pin 15 et Type DHT11

    //Initialisation des LED statuts
    pinMode(GPIO_PIN_LED_LOCK_ROUGE,OUTPUT);
    pinMode(GPIO_PIN_LED_OK_GREEN,OUTPUT);
    pinMode(GPIO_PIN_LED_HEAT_YELLOW,OUTPUT);

    digitalWrite(GPIO_PIN_LED_LOCK_ROUGE,HIGH);
    digitalWrite(GPIO_PIN_LED_OK_GREEN,HIGH);

        
        

 };


void loop() {
    
    
  }




