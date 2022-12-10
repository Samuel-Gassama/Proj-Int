/* Copyright (C) 2021 Alain Dube
 * All rights reserved.
 *
 * Projet Sac
 * Ecole du Web
 * Cours Objets connectés (c)2021
 *  
    @file     MyOledViewWifiAp.cpp
    @author   David Tremblay et Samuel Gassama
    @version  1.1 22/11/25

    Historique des versions
           Version    Date       Auteur       Description
           1.1        25/11/22  Samuel       Première version du logiciel


    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
*/

#ifndef MYOLEDVIEWWIFIAP_H
#define MYOLEDVIEWWIFIAP_H

#include <Adafruit_SSD1306.h>
#include "MyOledView.h"
#include <string>
#include <vector>
using std::vector;

class MyOledViewWifiAp: public MyOledView {
    
    public:
        void setNomDuSysteme(std::string val);
        void setSsIDDuSysteme(std::string val);
        void setPassDuSysteme(std::string val);

    private:
        std::string nomDuSysteme;
        std::string ssIDDuSysteme;
        std::string passDuSysteme;

        void display(Adafruit_SSD1306 *adafruit);
        void update(Adafruit_SSD1306 *adafruit);
      
};
#endif