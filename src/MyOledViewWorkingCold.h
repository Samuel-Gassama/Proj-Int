/**
    Class MyOledViewWorkingCOLD : Gestion d'une VUE pour le OLed
    @file MyOledViewWorkingCOLD.h 
    @author Alex De Souza
    @version 1.1 24/11/22 
    
    Historique des versions   
                            Versions  Date      Auteur      Description
                            1.1      17/11/22    Ald        Première version de la classe
                            
                            
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
        Aucune
    Autres librairies (à copier dans le répertoire lib)
        Aucune
    
**/

#ifndef MyOledViewWorkingCOLD_H
#define MyOledViewWorkingCOLD_H

#include <Adafruit_SSD1306.h>
#include "MyOledViewWorking.h"
#include <string>
#include <vector>
using std::vector;

class MyOledViewWorkingCOLD: public MyOledViewWorking {

    private:
        void display(Adafruit_SSD1306 *adafruit);
        void update(Adafruit_SSD1306 *adafruit);
};
#endif