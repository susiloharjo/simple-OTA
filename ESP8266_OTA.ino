#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

//Wifi Manager init
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager


  
void setup() {
   WiFiManager wifiManager;
     wifiManager.autoConnect("susiloharjo's device");
    Serial.println("");
    Serial.print("Connected to WiFi at ");
    Serial.print(WiFi.localIP());
    
  pinMode(LED_BUILTIN, OUTPUT); 
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
//  /WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
   ArduinoOTA.setHostname("susiloharjoDevice");

  // No authentication by default
   ArduinoOTA.setPassword((const char *)"admin");

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  
}

void loop() {
  ArduinoOTA.handle();
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(500);                 
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);

  
}
