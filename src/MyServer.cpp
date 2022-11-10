/**
    Gestion d'un serveur WEB
    @file MyServer.cpp
    @author Alain Dubé
    @version 1.1 20/11/20 
*/
#include <Arduino.h>
#include "MyServer.h"
using namespace std;

typedef std::string (*CallbackType)(std::string);
CallbackType MyServer::ptrToCallBackFunction = NULL;

//Exemple pour appeler une fonction CallBack
//if (ptrToCallBackFunction) (*ptrToCallBackFunction)(stringToSend); 
void MyServer::initCallback(CallbackType callback) {
    ptrToCallBackFunction = callback;
    }

void MyServer::initAllRoutes() { 
    currentTemperature = 3.3f;

    //Initialisation du SPIFF.
    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
        }

    //Route initiale (page html)
    this->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html", "text/html");
        });

    //Route du script JavaScript
    this->on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/script.js", "text/javascript");
        });
    // Route du style css pour l'index.html

    this->on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/style.css", "text/css");
        });
   
    // Route pour ajouter l'image sac.png

   this->on("/sac.png", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/sac.png", "");
        });
   
    // Route pour tester le bouton callback 

    // this->on("/button", HTTP_GET, [](AsyncWebServerRequest *request) { // ADDED ROUTE FOR CALLBACK
    //     std::string repString = "";
    //     Serial.println("button");
    //      if (ptrToCallBackFunction) repString = (ptrToCallBackFunction)("button Test"); //Exemple pour appeler une fonction CallBack
    //      String button = String(repString.c_str());
    //     request->send(200, "text/plain", button);
    //     });

        // Route fonction pour lire la mesure de la température du senseur 

       this->on("/getTemperatureSensor", HTTP_GET, [](AsyncWebServerRequest *request) {
        std::string repString = "";
        if (ptrToCallBackFunction) repString = (*ptrToCallBackFunction)("temperature");
        String temp = String(repString.c_str());
        request->send(200, "text/plain", temp);
        });

        // Route fonction pour récupérer l'API des bois

        this->on("/getAllWoodOptions", HTTP_GET, [](AsyncWebServerRequest *request) {
        Serial.println("getAllWoodOptions... ");
        HTTPClient http;
        String woodApiRestAddress = "http://api.qc-ca.ovh:2223/api/woods/getAllWoods/"; // ADRESSE DE L'API
        http.begin(woodApiRestAddress);
        http.GET();
        String response = http.getString();
        Serial.println(response);
        request->send(200, "text/plain", response);
        
    });
    

    // Route fonction pour récupérer le nom du du FOUR

        this->on("/getNomFour", HTTP_GET, [](AsyncWebServerRequest *request) {
        std::string repString = " ";
        if (ptrToCallBackFunction) repString = (*ptrToCallBackFunction)("askNomFour");
        String lireNomDuFour =String(repString.c_str());
        request->send(200, "text/plain", lireNomDuFour );
        });

    this->onNotFound([](AsyncWebServerRequest *request){
        request->send(404, "text/plain", "Page Not Found");
        });

    this->begin();
};

/************************************************************************************************************************/


// ADRESSE DE L'API : http://api.qc-ca.ovh:2223/bois?key=IlBv28V1NT81IvZWXVP126IZ6hJ5xd9fxIMP4gzIbvacr



  