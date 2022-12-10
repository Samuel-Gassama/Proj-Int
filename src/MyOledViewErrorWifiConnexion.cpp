/**
    Gestion d'une VUE pour le OLed
    @file MyOledViewErrorWifiConnexion.cpp
    @author David Tremblay et Samuel Gassama
    @version 1.1 21/11/30
*/
#include <Arduino.h>
#include "MyOledView.h"
#include "MyOledViewErrorWifiConnexion.h"
using namespace std;

//-------------------Setter----------------------
string MyOledViewErrorWifiConnexion::setNomDuSysteme(string valNom)
{

    this->NomDuSysteme = valNom;
    return "";
}

//--------------fonctions d'affichage--------------------
void MyOledViewErrorWifiConnexion::display(Adafruit_SSD1306 *display)
{
    
    display->clearDisplay();
    display->setTextSize(1);
    display->setCursor(1, 0);
    display->setTextSize(2);
    display->println("SAC System");
    display->setTextSize(1);
    display->setCursor(1, 20);
    display->println("AP configuration");
    display->setCursor(40, 20);
    display->println(this->NomDuSysteme.c_str());
    display->setCursor(1, 40);
    display->println("SSID : ");
    display->setCursor(40, 40);
    display->println(this->getTag("ssid").c_str());
    display->setCursor(1, 50);
    display->println("PASS : ");
    display->setCursor(40, 50);
    display->println(this->getTag("pass").c_str());
    display->display();
    delay(20);
    

    delay(20);
}
//--------------fonctions d'affichage--------------------
void MyOledViewErrorWifiConnexion::update(Adafruit_SSD1306 *update)
{
    update->setTextSize(1);

    update->setCursor(1, 0);
    update->println("AP configuration");
    update->setCursor(1, 20);
    update->println(this->NomDuSysteme.c_str());

    delay(20);

    delay(20);

    
}