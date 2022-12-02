/**
    Gestion d'une VUE pour le OLed
    @file MyOledViewErrorWifiApp.cpp
    @author Thanina Adda
    @version 1.1 21/11/30
*/
#include <Arduino.h>
#include "MyOledView.h"
#include "MyOledViewWifiAp.h"
using namespace std;
//-------------------Setter----------------------
string MyOledViewWifiAp::setNomDuSysteme(string valNom)
{

    this->NomDuSysteme = valNom;
    return "";
}

string MyOledViewWifiAp::setSslDuSysteme(string valSsl)
{

    this->SslDuSysteme = valSsl;
    return "";
}

string MyOledViewWifiAp::setPassDuSysteme(string valPass)
{

    this->PassDuSysteme = valPass;
    return "";
}
//--------------fonctions d'affichage--------------------
void MyOledViewWifiAp::display(Adafruit_SSD1306 *display)
{

    display->clearDisplay();
    display->setTextSize(1);

    display->setCursor(1, 0);
    display->println("Sac System");
    display->setCursor(1, 20);
    display->println(this->NomDuSysteme.c_str());
    display->setCursor(1, 40);
    display->println(this->SslDuSysteme.c_str());
    display->setCursor(1, 50);
    display->println(this->PassDuSysteme.c_str());
    display->display();
    delay(20);

    delay(20);
}
//--------------fonctions d'affichage--------------------
void MyOledViewWifiAp::update(Adafruit_SSD1306 *update)
{
    update->clearDisplay();
    update->setTextSize(1);
    update->setCursor(1, 0);
    update->println("Sac System Update");
    update->setCursor(1, 20);
    update->println(this->NomDuSysteme.c_str());
    update->setCursor(1, 40);
    update->println(this->SslDuSysteme.c_str());
    update->setCursor(1, 50);
    update->println(this->PassDuSysteme.c_str());
    update->display();
    delay(20);

    delay(20);
}