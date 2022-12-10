/**
    Class MyOledViewWorkingHEAT : Gestion d'une VUE pour le OLed
    @file MyOledViewWorkingHEAT.h 
    @author David Tremblay et Samuel Gassama
    @version 1.1 24/11/22 
    
    Historique des versions   
                            Versions  Date      Auteur      Description
                            1.1      17/11/22    Samuel        Première version de la classe
                            
                            
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
        Aucune
    Autres librairies (à copier dans le répertoire lib)
        Aucune
    
**/

#ifndef MyOledViewWorkingHEAT_H
#define MyOledViewWorkingHEAT_H

#include <Adafruit_SSD1306.h>
#include "MyOledViewWorking.h"
#include <string>
#include <vector>
using std::vector;

class MyOledViewWorkingHEAT: public MyOledViewWorking {

    private:
        void display(Adafruit_SSD1306 *adafruit);
        void update(Adafruit_SSD1306 *adafruit);
};
#endif