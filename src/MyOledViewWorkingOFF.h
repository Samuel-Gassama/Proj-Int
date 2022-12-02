/**
    Class MyOledViewWorkingHeat : Gestion d'une VUE pour le OLed
    @file MyOledViewWorkingHeat.h
    @author Thanina Adda
    @version 1.1 21/11/30

   
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps =
        Aucune
    Autres librairies (à copier dans le répertoire lib)
        Aucune

    Exemple d'utilisation

    myOledViewWorkingOff->setParams("temperature", vv.str());
    myOled->displayView(myOledViewWorkingOff);
       
**/


#ifndef MYOLEDVIEWWORKINGOFF
#define MYOLEDVIEWWORKINGOOFF
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MyOledViewWorking.h>

class MyOledViewWorkingOFF : public MyOledViewWorking
{
private:
    void display(Adafruit_SSD1306 *adafruit);
};
#endif