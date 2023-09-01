#include <Arduino.h>
#include "heltec.h"
#include "WiFi.h"

const int prg = 0;





void show(String text) {

  Heltec.display->clear();  // clear display

  Heltec.display->setFont(ArialMT_Plain_10);          //Font
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);  // Align
  Heltec.display->drawString(0, 0, text);             //write sting
  //Heltec.display->flipScreenVertically(); // Vertical mirroring

  Heltec.display->display();  // show strings on display
}

void blink() {
  digitalWrite(LED, HIGH);
  delay(60);
  digitalWrite(LED, LOW);
}

void clear() {
  Heltec.display->clear();
  Heltec.display->display();

}


void WifiConnect(String ssid, String pass){       // connect to other WiFi

  try{  
    WiFi.begin(ssid, pass);

    show("connected");
  } catch(...){
  show("WiFi not found");
  }
}


void newWiFi(String nssid, String npass){
  WiFi.mode(WIFI_AP);
  WiFi.softAP(nssid, npass);
  String message = "New WiFi. SSID:"+ nssid + " password:" + npass;
  show(message);
}

void setup() {

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  pinMode(prg, INPUT);

  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Enable*/, true /*Serial Enable*/);

 // WifiConnect("vlas", "vlasvlas"); // connection for try. Need change 

 newWiFi("Google", "OkGoogle" );
}

void loop() {

  if (Serial.available() > 0) {

    String text = Serial.readString();
    text.trim();

   
    if (text == "clear") {
      clear();

    } else {
      //String text = Serial.readString();  //create variable string "text" and add to "text" sting from port
      show(text);                         // call function "show" and send string "text"
      blink();                           //blink LED
    }
  }

  if (!digitalRead(prg)) {
    clear();
  }
  
}