/**
    Gestion d'un serveur WEB
    @file MyServer.cpp
    @author David Tremblay et Samuel Gassama
    @version 1.1 17/11/2022
*/
#include <Arduino.h>
#include "MyServer.h"
#include "ArduinoJson.h"

#include <soc/timer_group_struct.h>
#include <soc/timer_group_reg.h>
#include <HTTPClient.h>

using namespace std;

typedef std::string (*CallbackType)(std::string);
CallbackType MyServer::ptrToCallBackFunction = NULL;

//Exemple pour appeler une fonction CallBack
//if (ptrToCallBackFunction) (*ptrToCallBackFunction)(stringToSend); 
void MyServer::initCallback(CallbackType callback)
{
    ptrToCallBackFunction = callback;
}

void MyServer::initAllRoutes()
{
    currentTemperature = 3.3f;

    //---------------------- Route initialisation du SPIFFS ----------------------
    if (!SPIFFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    //---------------------- Route de la page index.html ----------------------
    this->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send(SPIFFS, "/index.html", "text/html");
    });

    //----------------------Route du script JavaScript ----------------------
    this->on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send(SPIFFS, "/script.js", "text/javascript");
    });

    //----------------------- Route pour le style.css -----------------------
    this->on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        request->send(SPIFFS, "/style.css", "text/css");
    });
   
    // ----------------------- Route pour l'image SAC.png
   this->on("/sac.png", HTTP_GET, [](AsyncWebServerRequest *request)
   {
        request->send(SPIFFS, "/sac.png", "");
    });

    // ----------------------- Récupération de la température  ------------------------------
    this->on("/getTemperatureSensor", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        std::string repString = "";
        if (ptrToCallBackFunction) repString = (*ptrToCallBackFunction)("temperature");
        String temp = String(repString.c_str());
        request->send(200, "text/plain", temp);
    });

    //------------------------------ Récupération des bois avec l'api --------------------------------
    this->on("/getAllWoodOptions", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        if (ptrToCallBackFunction) (*ptrToCallBackFunction)("button getAllWoodOptions");
        HTTPClient http;     
        String serverTo = "http://api.qc-ca.ovh:2223/api/woods/getAllWoods/";
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

    // ---------------------- Récupérer les caractéristiques du bois -----------------------
    this->on("/getWoodCaracteristiques", HTTP_POST, [](AsyncWebServerRequest *request)
    {
        Serial.println("getWoodCaracteristiques...");
        String wood;

        if (request->hasParam("wood", true))
        {
            wood = request->getParam("wood", true)->value();
            Serial.println("wood1: " + wood);
        }
        else
        {
            Serial.println("Erreur de parametre");
        }
        
        HTTPClient http;
        String woodApiRestAddress = "http://api.qc-ca.ovh:2223/api/woods/getWood/";
        woodApiRestAddress += wood;
        http.begin(woodApiRestAddress);
        http.addHeader("Authorization", "Bearer 2e550451f21d19dc726b54e574d6d6b76665ade19f703af2a26384cf2d3adf9a8e9a5e28270471fa2a6a3c1982aafa2be5ff14179cbfbf299a189846dfc45101");

        // Specify content-type header
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");

        int httpResponseCode = http.GET();
        Serial.println("httpResponseCode: " + String(httpResponseCode));

        String response;
        if (httpResponseCode > 0)
        {
            response = http.getString();
            Serial.println("response: " + response);
        }
        else
        {
            Serial.println("Error on HTTP request");
        }
        http.end();

        DynamicJsonDocument doc(2048);
        deserializeJson(doc, response);
        String tempToSend;
        for (JsonObject elem : doc.as<JsonArray>())
        {
            String woodName = elem["name"];
            String woodType = elem["type"];
            String woodOrigin = elem["origin"];
            String WoodDryingTime = elem["dryingTime"];
            String woodTemperature = elem["temperature"];

            tempToSend+= String("Bois") + String("&") + woodName + String("&");
            tempToSend+= String("Type") + String("&") + woodType + String("&");
            tempToSend+= String("Origin") + String("&") + woodOrigin + String("&");
            tempToSend+= String("Sechage") + String("&") + WoodDryingTime + String("&");
            tempToSend+= String("Temps") + String("&") + woodTemperature + String("&");
            Serial.println("tempToSend: " + tempToSend);

            std::string repString = "";
            String stringToSend = "tellCaracteristiques ";
            stringToSend += String("Bois") + String(" ") + woodName + String(" ");
            stringToSend += String("Type") + String(" ") + woodType + String(" ");
            stringToSend += String("Origin") + String(" ") + woodOrigin + String(" ");
            stringToSend += String("Sechage") + String(" ") + WoodDryingTime + String(" ");
            stringToSend += String("Temps") + String(" ") + woodTemperature + String(" ");

            if (ptrToCallBackFunction) repString = (*ptrToCallBackFunction)(stringToSend.c_str());

            request->send(200, "text/plain", tempToSend);
            break;
        }
    });
    
    // ----------------------- Fonction pour lire l'état du four -----------------------
    this->on("/lireStatus", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        std::string repString = "";

        if (ptrToCallBackFunction) repString = (*ptrToCallBackFunction)("askStatus");

        String lireStatus = String(repString.c_str());
        request->send(200, "text/plain", lireStatus);
    });


    // ----------------------- Fonction pour changer l'état du four -----------------------
    this->on("/setEtatFour", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        if (request->hasParam("etat"))
        {
            request->send(200, "text/plain",  "Etat changed");
            String action = "setEtatFour" ;
            String inputEtat = request->getParam("etat")->value();
            String donnee = action + " " + inputEtat;
            if(ptrToCallBackFunction)(*ptrToCallBackFunction)(donnee.c_str());
        }
        else
        {
            request->send(400, "text/plain", "Etat not changed");
        }
    });

    this->begin();

    //--------------------------- route recuperer le nom du four  ---------------------------
    this->on("/getNomFour", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        std::string repString = " ";
        if (ptrToCallBackFunction) repString = (*ptrToCallBackFunction)("askNomFour");
        String lireNomDuFour =String(repString.c_str());
        request->send(200, "text/plain", lireNomDuFour );
    });

    this->onNotFound([](AsyncWebServerRequest *request)
    {
        request->send(404, "text/plain", "Page Not Found");
    });

    this->begin();
   
    //--------------------------- route déclencher le four  ---------------------------
    this->on("/declencheFour", HTTP_POST, [](AsyncWebServerRequest *request)
    {
        String tmp = "";

        if (request->hasParam("temperature", true))
        {
            String temperature = request->getParam("temperature", true)->value();
            tmp = temperature;
        }
        if (request->hasParam("duree", true))
        {
            String duree = request->getParam("duree", true)->value();
            tmp = tmp + " " + duree;
        }

        tmp = "declencheFour " + tmp;

        if (ptrToCallBackFunction) (*ptrToCallBackFunction)(tmp.c_str());
        request->send(204); 
    });
};