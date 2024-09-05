#ifndef SERVER_COMMUNICATION_H
#define SERVER_COMMUNICATION_H

#include <ESP8266WiFi.h>

const char* serverHost = "your.server.address";
const int serverPort = 3000;

void sendToServer(String data) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    if (client.connect(serverHost, serverPort)) {
      client.println("POST /attendance HTTP/1.1");
      client.println("Host: " + String(serverHost));
      client.println("Content-Type: application/x-www-form-urlencoded");
      client.println("Content-Length: " + String(data.length()));
      client.println();
      client.println(data);
      client.stop();
    }
  } else {
    Serial.println("WiFi not connected");
  }
}

#endif
