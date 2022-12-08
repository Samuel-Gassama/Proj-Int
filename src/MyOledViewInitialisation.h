
/**
    Class MyOledView : Gestion d'une VUE pour le OLed
    @file MyOledViewInitialisation.h
    @author Samuel GASSAMA
    @version 1.0 11/08/2021
    
    Historique des versions   
                            Versions  Date      Auteur      Description
                            1.1      11/08/21   Samuel       Première version de la classe
                            
                            
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
        Aucune
    Autres librairies (à copier dans le répertoire lib)
        Aucune
    
    Exemple d'utilisation 
        //Définition 
            #include "MyOledView.h"
            class MyOledViewInitialisation: public MyOledView {
                public:
                
                private:
                    //Mettre la vue dans cette méthode
                    void display( Adafruit_SSD1306 *adafruit);
        ...
        //Utilisation
        myOledViewInitialisation = new MyOledViewInitialisation();
        myOled->displayView(myOledViewInitialisation);
**/


#include <Adafruit_SSD1306.h>
#include <string>
#include "MyOledView.h"

#ifndef MYOLEDVIEWINITIALISATION_H
#define MYOLEDVIEWINITIALISATION_H

class MyOledViewInitialisation : public MyOledView  {

    public: 

    void display( Adafruit_SSD1306 *adafruit);
    void update(Adafruit_SSD1306 *adafruit);
    void setIdDuSysteme(std::string);
    void setNomDuSysteme(std::string);

    void setSensibiliteBoutonAction(std::string val);
    void setSensibiliteBoutonReset(std::string val);

    private:
     
    std::string NomDuSysteme;
    std::string IdDuSysteme;
    std::string SensibiliteButtonAction;
    std::string SensibiliteButtonReset;

};

#endif