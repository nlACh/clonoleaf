#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WS2812FX.h>
#include "config.h"

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(HTTP_PORT);
WS2812FX strip = WS2812FX(LED, PIN, LED_TYPE+LEDKHZ);

bool autoCycle = false;
unsigned long now = 0L, lastTime = 0L;
int mode=0;

// Request handlers
void handlest(){
  strip.setMode(FX_MODE_STATIC);
  server.send(200, "application/json", "{\n\t\"ask\":\"static\"\r\n}\n");
}

void handleRC(){
  strip.setMode(FX_MODE_RAINBOW_CYCLE);
  server.send(200, "application/json", "{\n\t\"ask\":\"rainbowCycle\"\r\n}\n");
}

void handleBR(){
  strip.setMode(FX_MODE_BREATH);
  server.send(200, "application/json", "{\n\t\"ask\":\"breath\"\r\n}\n");
}

void handle(){
  autoCycle = true;
  server.send(200, "application/json", "{\n\t\"ask\":\"auto\"\r\n}\n");
}

// Main Program
void setup(void) {
  // First disconnect wifi... otherwise static config wont work
  WiFi.disconnect();
  
  pinMode(PIN, OUTPUT);
  Serial.begin(115200);

  strip.init();
  strip.setBrightness(100);
  strip.setSpeed(200);
  strip.setColor(DEFAULT_COLOR);
  strip.setMode(FX_MODE_BREATH);
  strip.start();
  // Static IP and other stuff.
  #ifdef STATIC_IP
  IPAddress ip(192,168,0,77);
  IPAddress gateway(192,168,0,1);
  IPAddress subnet(255,255,255,0);
  const char* deviceName = DEVICE_NAME;
  WiFi.hostname(deviceName);
  WiFi.config(ip, gateway, subnet);
  #endif
  
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

  /**
   * Defining some server functions.
   **/
  server.on("/rainbowCycle", handleRC);
  server.on("/static", handlest);
  server.on("/breath", handleBR);
  server.on("/auto", handle);
  server.on("/inline", []() {
    server.send(200, "application/json", "{\n\t\"ask\":\"CLONOLEAF\"\r\n}\n");
  });

  server.begin();
  Serial.println("HTTP server started");
}


void loop(void) {
  strip.service();
  server.handleClient();
  now = millis();
  if( autoCycle && (now - lastTime)>=TIMECYCLE){
    strip.setMode(mode);
    mode = (mode<=NUM_MODES) ? mode++ : 0;
  }
}