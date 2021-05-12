/* 
Modified according to the MIT licensing agreement
Original made by Ray Burnette, available at: https://github.com/witussk/wifi-sniffer-burnette-backup
*/

#include <ESP8266WiFi.h>
#include "./functions.h"

// Variable setup
#define disable 0
#define enable  1
unsigned int channel = 1;

void setup() {
  Serial.begin(57600);
  Serial.println(F("Final Year Project - MAC Address sniff test"));
  Serial.println(F("Type:   /-------MAC------/-----WiFi Access Point SSID-----/  /----MAC---/  Chnl  RSSI"));

  // Wi-Fi Module mode setup
  wifi_set_opmode(STATION_MODE);           
  wifi_set_channel(channel);
  wifi_promiscuous_enable(disable);
  wifi_set_promiscuous_rx_cb(promisc_cb);   
  wifi_promiscuous_enable(enable);
}

// Main loop, loops through individual Wi-Fi Channels to scan for MAC addresses
void loop() {
  channel = 1;
  wifi_set_channel(channel);

  while (true) {
    nothing_new++;                         
    if (nothing_new > 200) {
      nothing_new = 0;
      channel++;

      // Scans all 14 2.4 GHz channels
      if (channel == 15) break;             
      wifi_set_channel(channel);
    }

    // Delay needed not to overload the SDK
    delay(1);

    // When serial enabled
    if ((Serial.available() > 0) && (Serial.read() == '\n')) {
      Serial.println("\n-------------------------------------------------------------------------------------\n");
      for (int u = 0; u < clients_known_count; u++) print_client(clients_known[u]);
      for (int u = 0; u < aps_known_count; u++) print_beacon(aps_known[u]);
      Serial.println("\n-------------------------------------------------------------------------------------\n");
    }
  }
}