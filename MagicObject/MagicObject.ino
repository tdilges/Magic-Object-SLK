#include "Freenove_WS2812_Lib_for_ESP32.h"
#include "Arduino.h"
#include "HardwareSerial.h"
#include <WiFi.h>
//#include <Adafruit_NeoPixel.h> mal reinschauen

// LED Settings
#define LEDS_COUNT  1
#define LEDS_PIN	48
#define CHANNEL		0

// Farbkonstanten-definitionen

/* to-do: Vanessa, Maren, Katharina

Bitte hier sinnvolle Konstanten für Farben inkl. deren Farbcodes definieren!

keine Farbnamen, sondern fehler-funktionalitäten
eher setStat statt setColor



Notizen 05.05.
zeitvar -> letzter run und aktuelle zeit
vergleich zeitdifferenz als delay-ersatz
blocking operation
starttimer millis(); nanos();




*/

//Router / WIFI Settings:
#define NETWORK_NAME "IBB_AudioAP" // entsprechend anpassen
#define PASSWORD "JonnyFantastic#"    // entsprechend anpassen


//Deklarationen
//void setColor(int color);
Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);


//BOOTWARE
void setup() {
   Serial.begin(9600);
 // ScanWiFiNetwork();
  Serial.println("\nSetup start ...");
  connectToWiFi();
  strip.begin();
  setColor(40);
  strip.show();
  //strip.setBrightness(100);
  delay(1000); 
  Serial.println("\nSetup abgeschlossen ...");
}

void loop() {
//Serial.println("..............................");
//Serial.println("Farbe wird angepasst.");
//setColor(40);
//strip.show();
//Serial.println("Farbe erfolgreich angepasst.");
//strip.setBrightness(10); //dokumentation checken
//Serial.println("Regulaerer Betriebsmodus aktiv.");
//delay(500);
//setColor(255);
//strip.show();
//delay(500);
checkWiFistatus();

}

// Set Color
void setColor(int color){
//Serial.println("setcolor");
    
      strip.setLedColorData(0, strip.Wheel(color));
    
    
        //strip.show();
        //strip.show(); //dokumentation checken
}


// WLAN Connection
void connectToWiFi() {
  WiFi.mode(WIFI_STA); //WIFI-Einstellungen sind statisch.
  WiFi.begin(NETWORK_NAME, PASSWORD);
  Serial.println("WLAN Verbindung wird hergestellt. Bitte warten ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.print("\nWLAN Verbindung hergestellt. Die IP-Adresse des Magic Objects lautet: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC-Adresse: ");
  Serial.println(WiFi.macAddress());
}



void checkWiFistatus () {
  Serial.println("Ab jetzt wird Wlan gechecked");
  delay(10000);
  
  /* Wenn Status gleich 3, 
  dann leuchte blau 
  ansonsten
  wenn Status nicht gleich 3
  dann leuchte rot*/
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Status ist nicht 3 = Nicht verbunden");
    //strip.begin();
    setColor(255);
    strip.show();
    Serial.println("Es sollte jetzt rot leuchten");
  }
  else (WiFi.status() == WL_CONNECTED); { // if geht auch
    Serial.println("Status ist 3 = Verbunden");
    //strip.begin();
    setColor(170);
    strip.show();
    Serial.println("Es sollte jetzt blau leuchten");
    Serial.print("\nWLAN Verbindung hergestellt. Die IP-Adresse des Magic Objects lautet: ");
    Serial.println(WiFi.localIP());
    Serial.print("MAC-Adresse: ");
    Serial.println(WiFi.macAddress());
  }
}







/*
// Netzwerk Scan 
void ScanWiFiNetwork(){
  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
      Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
     // Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      delay(10);
    }
  }
  Serial.println("");

  // Wait a bit before scanning again
  delay(5000);
}
*/