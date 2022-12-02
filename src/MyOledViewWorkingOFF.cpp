/**
    Gestion d'une VUE pour le OLed
    @file MyOledViewWorkingOFF.cpp
    @author Thanina Adda
    @version 1.1 21/09/20
*/
#include <Arduino.h>
#include "MyOledView.h"
#include "MyOledViewWorkingOFF.h"
#include "MyOled.h"
using namespace std;


//--------------fonctions d'affichage--------------------
void MyOledViewWorkingOFF::display(Adafruit_SSD1306 *display)
{
    MyOledViewWorking::update(display);
    display->setTextSize(1);

    display->setCursor(1, 0);
    display->setTextSize(2);
    display->println("Sac System");
    display->setTextSize(1);
    display->setCursor(70, 20);
    display->println("Waiting");
    delay(20);
    display->display();

    delay(20);
}
