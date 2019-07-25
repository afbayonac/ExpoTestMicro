#include <header.h>

IPAddress red(192, 168, 4, 4);
IPAddress gateway(192, 168, 4, 4);
IPAddress mask(255,255,255,0);

CustomServer server;

/* Set these to your desired credentials. */
const char *ssid = "local_espwrom02";
const char *password = "123456789";
const char *domain = "expotest";

void setup() {
  void (*DEBUG)(const String str);
  DEBUG = PRINT_DEBUG;

  Serial.begin(115200);
  PRINT_DEBUG("\n\n [Init debug Monitor] \n");
  /* init as access point */
  initAP();
  /* init domain name */
  initmDNS();

  server.begin(DEBUG);
  /* init File System */
  initSPIFFS();

  /* OTA */ 
  ArduinoOTA.onStart([](){
    if (ArduinoOTA.getCommand() == U_FLASH) {
      PRINT_DEBUG("\n\nSTART UPLOAD SKEACH\n");
    } else {
      PRINT_DEBUG("\n\nSTART UPLOAD FILESYSTEM\n");
      SPIFFS.end();
    }
  });

  ArduinoOTA.onEnd([](){
    PRINT_DEBUG("END");
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

}

void loop() {
  MDNS.update();
  server.handle();
  ArduinoOTA.handle();
}

void initAP() {
  /* Configure access point */

  PRINT_DEBUG("\n \tSetting soft-AP configuration ... ");

  PRINT_DEBUG(WiFi.softAPConfig(red, gateway, mask) ? "ready" : "Failed");
  PRINT_DEBUG("\n \tSetting soft-AP ...");

  PRINT_DEBUG(WiFi.softAP(ssid, password, 5) ? "ready" : "Failed!");
  PRINT_DEBUG("\n  \tSoft-AP IP address = ");
  PRINT_DEBUG(WiFi.softAPIP().toString());
  PRINT_DEBUG("\n");
}

void initmDNS() {
  if (!MDNS.begin(domain)) {
    PRINT_DEBUG("\tError setting up MDNS responder!");
    while (1) delay(1000);  
  }

  PRINT_DEBUG("\tmDNS responder started, connect to http://");
  PRINT_DEBUG(domain);
  PRINT_DEBUG(".local \n");

  MDNS.addService("http", "tcp", 80);
}

void initSPIFFS() {
  SPIFFS.begin();  
  Dir dir = SPIFFS.openDir("/");
  PRINT_DEBUG("\n\tList files in systemfile: \n");
  while (dir.next()) {
    PRINT_DEBUG("\t - FS File: ");
    PRINT_DEBUG(dir.fileName().c_str());
    PRINT_DEBUG("\n");
  }
}
