 #include <MyOledViewWifiAp.h>
 #include <Arduino.h>
 #include <Adafruit_SSD1306.h>
 #include <Adafruit_GFX.h>
 #include <Adafruit_I2CDevice.h>

 using namespace std;


void MyOledViewWorkingWifiAP::setNomDuSysteme(string val){
    NomDuSysteme = val;
}

void MyOledViewWorkingWifiAP::setSsIDDuSysteme(string val){
    IdDuSysteme = val;
}

void MyOledViewWorkingWifiAP::setpassDuSysteme(string val){
    passDuSysteme = val;
}

 void MyOledViewWorkingWifiAP::update(Adafruit_SSD1306 *adafruit){
     Serial.println("Update Display Adafruit");
 }

 void MyOledViewWorkingWifiAP::display(Adafruit_SSD1306 *adafruit){

     char strNom[128];
     char strId[128];
     char strPass[128];
    sprintf(strNom,"ID : %s", NomDuSysteme.c_str());
    sprintf(strId,"SSID: %s", IdDuSysteme.c_str());
    sprintf(strPass,"PASS : %s", passDuSysteme.c_str());

       adafruit-> setTextSize(2);
       adafruit->setTextColor(WHITE);
       adafruit->setCursor(0,0);
       adafruit->println(strNom);
       adafruit->setTextColor(BLACK, WHITE); // 'inverted' text
       adafruit->setTextSize(1);
       adafruit->setTextColor(WHITE);
       adafruit->println(strId); 
       adafruit->println(strPass); 
       //display.println(0xDEADBEEF, HEX);
       adafruit->display();
 }