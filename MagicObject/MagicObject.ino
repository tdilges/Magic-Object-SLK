#include "Freenove_WS2812_Lib_for_ESP32.h"
#include "Arduino.h"
#include "HardwareSerial.h"
#include <WiFi.h>


#define LEDS_COUNT  1
#define LEDS_PIN	48
#define CHANNEL		0

#define NETWORK_NAME "Hogwarts"
#define PASSWORD "alohomora"

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);

void setup() {
 
 /* Logik zum Clearen des Serial Monitors -> Funzt noch nicht
  Serial.write(27);       // ESC command
  Serial.println("[2J");    // clear screen command
  Serial.write(27);
  Serial.println("[H");     // cursor to home command
  */ //Clear-Logik Ende
  Serial.begin(9600);
  ScanWiFiNetwork();
  connectToWiFi();
  strip.begin();
  strip.setBrightness(20);
    
}

void loop() {
led();

}



void led(){

    for (int j = 0; j < 255; j += 2) {
    for (int i = 0; i < LEDS_COUNT; i++) {
      strip.setLedColorData(i, strip.Wheel((i * 256 / LEDS_COUNT + j) & 255)); // -> Liefert einen 8-Bit Zahlenwert an das Board (256 Werte, 0-255)
    }
    
    strip.show();
    delay(500);
  }  
}

// mit WLAN Connecten
void connectToWiFi() {
  WiFi.mode(WIFI_STA); //WIFI-Einstellungen statisch sind.
  WiFi.begin(NETWORK_NAME, PASSWORD);
  Serial.println("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    // led(0, 255, 0);
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}



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