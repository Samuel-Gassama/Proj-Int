/**
    Class MyOledViewWorkingOFF : Gestion d'une VUE pour le OLed
    @file MyOledViewWorkingOFF.h 
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

#ifndef MyOledViewWorkingOFF_H
#define MyOledViewWorkingOFF_H

#include <Adafruit_SSD1306.h>
#include "MyOledViewWorking.h"
#include <string>
#include <vector>
using std::vector;

class MyOledViewWorkingOFF: public MyOledViewWorking {

    private:
        void display(Adafruit_SSD1306 *adafruit);
};
#endif 