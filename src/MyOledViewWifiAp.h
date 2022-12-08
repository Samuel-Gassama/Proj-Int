 #include <Adafruit_SSD1306.h>
 #include <string> 
 #include "MyOledView.h"

#ifndef MYOLEDVIEWWORKINGWIFIAP_H
#define MYOLEDVIEWWORKINGWIFIAP_H

 class MyOledViewWorkingWifiAP : public MyOledView{

    public :

      void display( Adafruit_SSD1306 *adafruit);
    void update(Adafruit_SSD1306 *adafruit);
       void setNomDuSysteme(std::string val);
       void setSsIDDuSysteme(std::string val);
       void setpassDuSysteme(std::string val);

    private:
     
        std::string NomDuSysteme;
        std::string IdDuSysteme; 
        std::string passDuSysteme;

         //virtual void update(Adafruit_SSD1306 *adafruit) = 0;
         //virtual void display( Adafruit_SSD1306 *adafruit) = 0;


 };

 #endif