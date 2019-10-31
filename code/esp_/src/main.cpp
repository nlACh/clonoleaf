#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WS2812FX.h>
#include "config.h"


#ifdef STATIC_IP
  IPAddress ip(192,168,0,77);
  IPAddress gateway(192,168,0,1);
  IPAddress subnet(255,255,255,0);
  const char* deviceName = DEVICE_NAME;
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(HTTP_PORT);




void setup(void) {
  // First disconnect wifi... otherwise static config wont work
  WiFi.disconnect();
  
  pinMode(PIN, OUTPUT);
  Serial.begin(115200);

  WiFi.hostname(deviceName);
  WiFi.config(ip, gateway, subnet);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/inline", []() {
    server.send(200, "application/json", "{\n\t\"ask\":\"CLONOLEAF\"\r\n}\n");
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}