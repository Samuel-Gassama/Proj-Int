/**
    Gestion d'un serveur WEB
    @file MyServer.cpp
    @author Alain Dubé
    @version 1.1 20/11/20 
*/
#include <Arduino.h>
#include "MyServer.h"
#include "ArduinoJson.h"
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

        this->on("/getAllWoodOptions", HTTP_GET, [](AsyncWebServerRequest *request)
        {
            if (ptrToCallBackFunction) (*ptrToCallBackFunction)("button getAllWoodOptions");
            HTTPClient http;     
            String serverTo = "http://api.qc-ca.ovh:2223/api/woods/getAllWoods/"; //adresse du serveur WEB
            bool httpInitResult = http.begin(serverTo);

            if (httpInitResult == false)
            {
                Serial.println("Erreur de connection au serveur");
            }
            http.addHeader("Authorization", "Bearer 2e550451f21d19dc726b54e574d6d6b76665ade19f703af2a26384cf2d3adf9a8e9a5e28270471fa2a6a3c1982aafa2be5ff14179cbfbf299a189846dfc45101");
            
            int httpCode = http.GET();
            Serial.println("httpCode: " + String(httpCode));
            if (httpCode > 0)
            {
                if (httpCode == HTTP_CODE_OK)
                {
                    String infoBois;
                    String payload = http.getString();
                    Serial.println(payload);
                    StaticJsonDocument<2048> doc;
                    deserializeJson(doc, payload);
                    JsonObject elem = doc.as<JsonObject>();
                    String results = elem["results"].as<String>();

                    Serial.println("Payload: " + payload);
                    request->send(200, "text/plain", payload);
                }
            }
            else
            {
                request->send(401, "text/plain", "Erreur de connection au serveur");
            }
            
            http.end(); 
    });
    
    this->on("/getWoodCaracteristiques", HTTP_GET, [](AsyncWebServerRequest *request)
        {
            if (ptrToCallBackFunction) (*ptrToCallBackFunction)("button getWoodCaracteristiques");
            AsyncWebParameter* p = request->getParam("nomBois");
            HTTPClient http;     
            String serverTo = "http://api.qc-ca.ovh:2223/api/woods/getWood/" + p->value(); //adresse du serveur WEB
            Serial.println(serverTo);

            bool httpInitResult = http.begin(serverTo);

            if (httpInitResult == false)
            {
                Serial.println("Erreur de connection au serveur");
            }
            http.addHeader("Authorization", "Bearer 2e550451f21d19dc726b54e574d6d6b76665ade19f703af2a26384cf2d3adf9a8e9a5e28270471fa2a6a3c1982aafa2be5ff14179cbfbf299a189846dfc45101");
            
            int httpCode = http.GET();
            Serial.println("httpCode: " + String(httpCode));
            if (httpCode > 0)
            {
                if (httpCode == HTTP_CODE_OK)
                {
                    String infoBois;
                    String payload = http.getString();
                    Serial.println(payload);
                    StaticJsonDocument<2048> doc;
                    deserializeJson(doc, payload);
                    JsonObject elem = doc.as<JsonObject>();
                    String results = elem["results"].as<String>();

                    Serial.println("Payload: " + payload);
                    request->send(200, "text/plain", payload);
                }
            }
            else
            {
                request->send(401, "text/plain", "Erreur de connection au serveur");
            }
            
            http.end(); 
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



  