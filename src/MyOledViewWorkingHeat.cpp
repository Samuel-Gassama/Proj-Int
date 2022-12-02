/**
    Gestion d'une VUE pour le OLed
    @file MyOledViewWorkingHeat.cpp
    @author Thanina Adda
    @version 1.1 21/09/20
*/
#include <Arduino.h>
#include "MyOledView.h"
#include "MyOledViewWorkingHeat.h"
#include "MyOled.h"
using namespace std;
//--------------fonctions d'affichage--------------------
void MyOledViewWorkingHeat::display(Adafruit_SSD1306 *display)
{
    display->setTextSize(1);

    display->setCursor(1, 0);
    display->setTextSize(2);
    display->println("Sac System");
    display->setTextSize(1);
    display->setCursor(70, 20);
    display->println("Heat");
    delay(20);
    display->display();

    delay(20);
}
//--------------fonctions d'affichage--------------------
void MyOledViewWorkingHeat::update(Adafruit_SSD1306 *update)
{
    MyOledViewWorking::update(update);
    update->setCursor(1, 0);
    update->setTextSize(2);
    update->println("Sac System");
    update->setTextSize(1);
    update->setCursor(70, 20);
    update->println("Heat");
    delay(20);
    update->display();
}
