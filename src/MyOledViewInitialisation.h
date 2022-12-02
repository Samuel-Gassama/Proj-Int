/**
    Class MyOledViewInitlisation : Gestion d'une VUE pour le OLed
    @file MyOledViewInitlisation.h
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
    myOledViewInitialisation->setNomDuSysteme("INITILISATION");
    myOledViewInitialisation->setIdDuSysteme("id : ID3944");
    myOled->displayView(myOledViewInitialisation);
**/

#ifndef MYOLEDVIEWINITIALISATION_H
#define MYOLEDVIEWINITIALISATION_H
#include <Adafruit_SSD1306.h>
#include <MyOledView.h>
#include <MyOled.h>
#include <string>
using std::vector;

class MyOledViewInitialisation : public MyOledView
{

public:
    std::string setNomDuSysteme(std::string valNom);
    std::string setIdDuSysteme(std::string valId);
    std::string setSensibliteBoutonActif(std::string valActif);
    std::string setSensibliteBoutonReset(std::string valReset);

private:
    std::string NomDuSysteme;
    std::string IdDuSysteme;
    std::string BoutonActif;
    std::string BoutonReset;
    void update(Adafruit_SSD1306 *adafruit);
    void display(Adafruit_SSD1306 *adafruit);
};
#endif