#include "Freenove_WS2812_Lib_for_ESP32.h"
#include "Arduino.h"
#include "HardwareSerial.h"
#include <WiFi.h>
//#include <Adafruit_NeoPixel.h>

// LED Settings
#define LEDS_COUNT  1
#define LEDS_PIN	48
#define CHANNEL		0

// Farbkonstanten-definitionen

/* to-do: Vanessa, Maren, Katharina

Bitte hier sinnvolle Konstanten für Farben inkl. deren Farbcodes definieren!

*/

//Router / WIFI Settings:
#define NETWORK_NAME "Hogwarts" // entsprechend anpassen
#define PASSWORD "alohomora"    // entsprechend anpassen


//Methoden-Deklaration
void setColor(int color);
Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);


//BOOTWARE
void setup() {
   Serial.begin(9600);
 // ScanWiFiNetwork();
  Serial.println("\nSetup start ...");
  connectToWiFi();
  strip.begin();
  setColor(170);
  strip.setBrightness(100); 
}

void loop() {
Serial.println("..............................");
Serial.println("Farbe wird angepasst.");
setColor(85);
Serial.println("Farbe erfolgreich angepasst.");
strip.setBrightness(10); 
Serial.println("Regulaerer Betriebsmodus aktiv.");
}

// Set Color
void setColor(int color){

    for (int j = 0; j < 255; j += 2) {
    for (int i = 0; i < LEDS_COUNT; i++) {
      //strip.setLedColorData(i, strip.Wheel((i * 256 / LEDS_COUNT + j) & 255)); // -> Liefert einen 8-Bit Zahlenwert an das Board (256 Werte, 0-255)
      strip.setLedColorData(i, strip.Wheel(color));
    }
    
    strip.show();
  }  
}


// WLAN Connection
void connectToWiFi() {
  WiFi.mode(WIFI_STA); //WIFI-Einstellungen statisch sind.
  WiFi.begin(NETWORK_NAME, PASSWORD);
  Serial.println("WLAN Verbindung wird hergestellt. Bitte warten ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.print("\nWLAN Verbindung hergestellt. Die IP-Adresse des Magic Objects lautet: ");
  Serial.print(WiFi.localIP());
  setColor(170);
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