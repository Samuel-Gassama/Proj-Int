/**
    Gestion d'une VUE pour le OLed  
    @file MyOledViewWorkingHEAT.cpp
    @author David Tremblay et Samuel Gassama
    @version 1.1 20/11/22 
*/

#include <Arduino.h>
#include "MyOledViewWorkingHEAT.h"

using namespace std;

void MyOledViewWorkingHEAT::display(Adafruit_SSD1306 *adafruit){

    MyOledViewWorking::display(adafruit);
    adafruit->clearDisplay();
    adafruit->setTextSize(1);
    adafruit->setCursor(70,20);
    adafruit->print("Heating");

    adafruit->setTextSize(2);
    adafruit->setCursor(10, 30);
    adafruit->print(getTag("temperature").c_str());

    adafruit->display();
}

void MyOledViewWorkingHEAT::update(Adafruit_SSD1306 *adafruit){
    Serial.println("Update my view MyOledViewWorkingCOLD");
}