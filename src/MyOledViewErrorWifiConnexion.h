/**
    Class MyOledViewErrorWifiConnexion : Gestion d'une VUE pour le OLed
    @file MyOledViewErrorWifiConnexion.h 
    @author Samuel GASSAMA
    @version 1.1 21/11/30 
    
                            
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
        Aucune
    Autres librairies (à copier dans le répertoire lib)
        Aucune
    
    Exemple d'utilisation 
    myOledViewErrorWifiConnexion->setParams("ssid", ssIDRandom.c_str());
    myOled->displayView(myOledViewErrorWifiConnexion); 
     
       
**/

#ifndef MYOLEDVIEWERRORWIFICONNEXION_H
#define MYOLEDVIEWERRORWIFICONNEXION_H

//Pour la gestion du Oled View Error Wifi Connexion
#include <Adafruit_SSD1306.h>
#include <MyOledView.h>
#include <MyOled.h>
#include <string>
using std::vector;

class MyOledViewErrorWifiConnexion : public MyOledView {
    
    public:

        std::string  setNomDuSysteme(std::string valNom);

    private:
        
        std::string NomDuSysteme;
         void  update(Adafruit_SSD1306 *adafruit);
         void display( Adafruit_SSD1306 *adafruit);
      
};
#endif