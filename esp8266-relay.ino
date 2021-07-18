#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "config.h"

#define PIN_RELAY 0

ESP8266WebServer server(80);

void handleHttpRequest() {
  digitalWrite(LED_BUILTIN, HIGH);

  if (server.hasArg("on")) {
    digitalWrite(PIN_RELAY, HIGH);
    server.send(200, "text/html", "<html><body><h1>Ok</h1><p>Relay ON</p></body></html>");
  } else if (server.hasArg("off")) {
    digitalWrite(PIN_RELAY, LOW);
    server.send(200, "text/html", "<html><body><h1>Ok</h1><p>Relay OFF</p></body></html>");
  }

  if (digitalRead(PIN_RELAY) == HIGH) {
    server.send(200, "text/html", "<html><body><h1>Ok</h1><p>Relay ON</p></body></html>");
  } else {
    server.send(200, "text/html", "<html><body><h1>Ok</h1><p>Relay OFF</p></body></html>");
  }
  
  server.send(200, "text/html", "<html><body><h1>Ok</h1></body></html>");
  digitalWrite(LED_BUILTIN, LOW);
}

void handleNotFound() {
  digitalWrite(LED_BUILTIN, HIGH);
  server.send(404, "text/html", "<html><body><h1>Not Found</h1></body></html>");
  digitalWrite(LED_BUILTIN, LOW);
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_RELAY, OUTPUT);
  
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi with IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleHttpRequest);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

  digitalWrite(PIN_RELAY, LOW);
}

void loop() {
  server.handleClient();
}
