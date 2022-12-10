/* Copyright (C) 2021 Alain Dube
 * All rights reserved.
 *
 * Projet Sac
 * Ecole du Web
 * Cours Objets connectés (c)2021
 *  
    @file     MyOledViewWifiAp.cpp
    @author   David Tremblay et Samuel Gassama
    @version  1.1 22/11/25

    Historique des versions
           Version    Date       Auteur       Description
           1.1        25/11/22  Samuel       Première version du logiciel


    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino

    */


#include <Arduino.h>
#include "MyOledViewWifiAp.h"
using namespace std;

void MyOledViewWifiAp::setNomDuSysteme(string val){
    nomDuSysteme = val;
}

void MyOledViewWifiAp::setPassDuSysteme(string val){
    passDuSysteme = val;
}

void MyOledViewWifiAp::setSsIDDuSysteme(string val){
    ssIDDuSysteme = val;
}

void MyOledViewWifiAp::update(Adafruit_SSD1306 *adafruit){
    Serial.println("Update my view MyOledViewWifiAp");
}

void MyOledViewWifiAp::display(Adafruit_SSD1306 *adafruit){

    adafruit->clearDisplay();
    adafruit->setTextSize(2);
    adafruit->setCursor(0, 0);
    adafruit->print(nomDuSysteme.c_str());

    adafruit->setTextSize(1);
    adafruit->setCursor(0,20);
    adafruit->print("AP configuration");

    adafruit->setTextSize(1);
    adafruit->setCursor(15, 30);
    adafruit->print("SSID: ");
    adafruit->print(ssIDDuSysteme.c_str());
    
    adafruit->setTextSize(1);
    adafruit->setCursor(15, 40);
    adafruit->print("PASS: ");
    adafruit->print(passDuSysteme.c_str());

    adafruit->display();
}