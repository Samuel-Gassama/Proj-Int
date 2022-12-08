/**
    Gestion d'une VUE pour le OLed  
    @file MyOledViewWorkingOFF.cpp
    @author Alex De Souza
    @version 1.1 20/11/22 
*/

#include <Arduino.h>
#include "MyOledViewWorkingOFF.h"

using namespace std;

void MyOledViewWorkingOFF::display(Adafruit_SSD1306 *adafruit){

    MyOledViewWorking::display(adafruit);

    adafruit->setTextSize(1);
    adafruit->setCursor(70,20);
    adafruit->print("Ready");

    adafruit->setTextSize(1);
    adafruit->setCursor(70, 30);
    adafruit->print(getTag("temperature").c_str());

    adafruit->display();
}