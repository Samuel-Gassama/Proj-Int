/**
    Gestion d'une VUE pour le OLed
    @file MyOledViewWorkingCold.cpp
    @author Thanina Adda
    @version 1.1 21/09/20
*/
#include <Arduino.h>
#include "MyOledView.h"
#include "MyOledViewWorkingCold.h"
#include "MyOled.h"
using namespace std;

//--------------fonctions d'affichage--------------------
void MyOledViewWorkingCold::display(Adafruit_SSD1306 *display)
{

    display->setTextSize(1);

    display->setCursor(1, 0);
    display->setTextSize(2);
    display->println("Sac System");
    display->setTextSize(1);
    display->setCursor(70, 20);
    display->println("Cold");
    delay(20);
    display->display();

    delay(20);
}
//--------------fonctions d'affichage--------------------
void MyOledViewWorkingCold::update(Adafruit_SSD1306 *update)
{
    MyOledViewWorking::update(update);
    update->setCursor(1, 0);
    update->setTextSize(2);
    update->println("Sac System");
    update->setTextSize(1);
    update->setCursor(70, 20);
    update->println("Cold");
    delay(20);
    update->display();
}
