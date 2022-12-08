/* Copyright (C) 2021 Alain Dube
 * All rights reserved.
 *
 * Projet Sac
 * Ecole du Web
 * Cours Objets connectés (c)2021
 *  
    @file     MyOledViewInitialisation.cpp
    @author   Maxence MAZEAU
    @version  1.1 21/08/15 

    Historique des versions
           Version    Date       Auteur       Description
           1.1        05/08/21  Maxence       Première version du logiciel


    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino

    */

#include <Arduino.h>
#include "MyOledViewInitialisation.h"
using namespace std;

void MyOledViewInitialisation::setNomDuSysteme(string value){
    NomDuSysteme = value;
}

void MyOledViewInitialisation::setIdDuSysteme(string value){
    IdDuSysteme = value;
}

void MyOledViewInitialisation::setSensibiliteBoutonAction(std::string val){
    SensibiliteButtonAction = val;
}

void MyOledViewInitialisation::setSensibiliteBoutonReset(std::string val){
    SensibiliteButtonReset = val;
}

void MyOledViewInitialisation::display(Adafruit_SSD1306 *adafruit){


    char strID[128];
    char strAction[128];
    char strReset[128];
    sprintf(strID,"ID : %s", IdDuSysteme.c_str());
    sprintf(strAction,"Bouton Action : %s", SensibiliteButtonAction.c_str());
    sprintf(strReset,"Bouton Reset : %s", SensibiliteButtonReset.c_str());

    adafruit->clearDisplay();
    adafruit->setTextSize(2);
    adafruit->setTextColor(WHITE);
    adafruit->setCursor(0,0);
    adafruit->println(NomDuSysteme.c_str());
    adafruit->setTextSize(1);
    adafruit->println(strID);
    adafruit->println("INITIALISATION");
    adafruit->println(strAction);
    adafruit->println(strReset);
    adafruit->display();
}

void MyOledViewInitialisation::update(Adafruit_SSD1306 *adafruit){
    display(adafruit);
}
