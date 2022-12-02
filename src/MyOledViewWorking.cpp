/**
    Gestion d'une VUE pour le OLed
    @file MyOledViewWorking.cpp
    @author Thanina Adda
    @version 1.1 21/09/20
*/
#include <Arduino.h>
#include "MyOledView.h"
#include "MyOledViewWorking.h"
#include "MyOled.h"
using namespace std;

//------------------------init------------------------
int MyOledViewWorking::init(string _id)
{
    MyOledView::init(_id);
    // Fire24x24Pointers[0] = const_cast<unsigned char *>(&Fire24x24Pointers_0[0]);
    // Fire24x24Pointers[1] = const_cast<unsigned char *>(&Fire24x24Pointers_1[0]);
    // Fire24x24Pointers[2] = const_cast<unsigned char *>(&Fire24x24Pointers_2[0]);
    // Fire24x24Pointers[3] = const_cast<unsigned char *>(&Fire24x24Pointers_3[0]);
    // Fire24x24Pointers[4] = const_cast<unsigned char *>(&Fire24x24Pointers_4[0]);
    // Fire24x24Pointers[5] = const_cast<unsigned char *>(&Fire24x24Pointers_5[0]);
    // Fire24x24Pointers[6] = const_cast<unsigned char *>(&Fire24x24Pointers_6[0]);
}

//--------------fonctions d'affichage--------------------
void MyOledViewWorking::display(Adafruit_SSD1306 *display)
{

    display->clearDisplay();
    display->setTextSize(1);

    display->setCursor(1, 0);
    display->setTextSize(2);
    display->println("Sac System");
    display->setTextSize(1);
    display->setCursor(1, 20);
    display->println(this->id().c_str());
    display->setCursor(1, 40);
    display->println(this->getTag("temperature").c_str());
    display->setCursor(1, 50);
    display->println(this->getTag("SslDuSysteme").c_str());
    delay(20);
    display->display();

    delay(20);
}
//--------------fonctions d'affichage--------------------
void MyOledViewWorking::update(Adafruit_SSD1306 *update)
{
    update->clearDisplay();
    update->setCursor(1, 0);
    update->setTextSize(2);
    update->println("Sac System");
    update->setTextSize(1);
    update->setCursor(1, 20);
    update->println(this->id().c_str());
    update->setTextSize(2);
    update->setCursor(1, 30);
    update->println(this->getTag("temperature").c_str());
    update->setTextSize(1);
    update->setCursor(1, 50);
    update->println(this->getTag("SslDuSysteme").c_str());
    delay(20);
    update->display();
}

//--------------fonctions d'affichage gifFire--------------------
void MyOledViewWorking::displayGifFire(Adafruit_SSD1306 *adafruitint)
{
}
//--------------fonctions d'affichage gifFireAnimated--------------------
void MyOledViewWorking::displayGifFireAnimated(Adafruit_SSD1306 *adafruitint, int positionX, int positionY)
{
}