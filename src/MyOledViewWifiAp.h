/**
    Class MyOledViewWifiAp : Gestion d'une VUE pour le OLed
    @file MyOledViewWifiAp.h
    @author Thanina Adda
    @version 1.1 21/11/02

   
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps =
        Aucune
    Autres librairies (à copier dans le répertoire lib)
        Aucune

    Exemple d'utilisation

    myOledViewWifiAp->setNomDuSysteme("Initialisation Wifi");
    myOled->updateCurrentView(myOledViewWifiAp);
       
**/

#ifndef MYOLEDVIEWWIFIAP_H
#define MYOLEDVIEWWIFIAP_H

#include <Adafruit_SSD1306.h>
#include <MyOledView.h>
#include <MyOled.h>
#include <string>
using std::vector;

class MyOledViewWifiAp : public MyOledView
{

public:
    std::string setNomDuSysteme(std::string valNom);
    std::string setSslDuSysteme(std::string valSsl);
    std::string setPassDuSysteme(std::string valPass);

private:
    std::string NomDuSysteme;
    std::string SslDuSysteme;
    std::string PassDuSysteme;
    void update(Adafruit_SSD1306 *adafruit);
    void display(Adafruit_SSD1306 *adafruit);
};
#endif