/**
    Gestion d'une VUE pour le OLed
    @file MyOledViewInitialisation.cpp
    @author Thanina Adda
    @version 1.1 21/11/30
*/

#include <Arduino.h>
#include "MyOledView.h"
#include "MyOledViewInitialisation.h"
using namespace std;

//--------------Setter--------------------
string MyOledViewInitialisation::setNomDuSysteme(string valNom)
{

    this->NomDuSysteme = valNom;
    return "";
}


string MyOledViewInitialisation::setIdDuSysteme(string valId)
{

    this->IdDuSysteme = valId;
    return "";
}


string MyOledViewInitialisation::setSensibliteBoutonActif(string valActif)
{

    this->BoutonActif = valActif;
    return "";
}

string MyOledViewInitialisation::setSensibliteBoutonReset(string valReset)
{

    this->BoutonReset = valReset;
    return "";
}

//--------------fonctions d'affichage--------------------
void MyOledViewInitialisation::display(Adafruit_SSD1306 *display)
{
    display->setTextSize(1);

    display->setCursor(1, 0);
    display->setTextSize(2);
    display->println("SAC System");
    display->setTextSize(1);
    display->setCursor(1, 20);
    display->println(this->NomDuSysteme.c_str());
    display->println(this->IdDuSysteme.c_str());
    display->println("Bouton ACTIF: ????");
    display->println("Bouton RESET: ????");
    delay(20);
    display->display();

    delay(20);
}
//--------------fonctions d'affichage--------------------
void MyOledViewInitialisation::update(Adafruit_SSD1306 *update)
{

    update->clearDisplay();
    update->setTextSize(1);
    update->setCursor(1, 0);
    update->setTextSize(2);
    update->println("SAC System");
    update->setTextSize(1);
    update->setCursor(1, 20);
    update->println(this->NomDuSysteme.c_str());
    update->println(this->IdDuSysteme.c_str());
    update->println(this->BoutonActif.c_str());
    update->println(this->BoutonReset.c_str());
    delay(20);
    update->display();
    delay(20);


}