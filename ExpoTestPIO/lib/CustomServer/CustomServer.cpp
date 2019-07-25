#include <CustomServer.h>

CustomServer::CustomServer(/* args */) {
}

CustomServer::~CustomServer() {
}

void CustomServer::begin(void (* DEBUG)(const String str)) {
    PRINT_DEBUG = DEBUG;
    server.on("/read/humidity", HTTP_GET, [&]{readHumidity();});
    server.on("/read/temperature", HTTP_GET, [&]{readTemperature();});
    server.onNotFound([&] {hadlerNotFound();});
    server.begin();
    dht.begin();
}

void CustomServer::handle() {
    server.handleClient();
}

void CustomServer::cors() {
    /* No test */
    PRINT_DEBUG("\n\tCORS request\n");
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Methods", "PUT, POST, GET, OPTIONS");
    server.sendHeader("Access-Control-Allow-Headers", "origin, x-requested-with, content-type");
    server.send(204);
}

void CustomServer::readHumidity() {
    PRINT_DEBUG("\n\tRequest Humedity\n");
    String h = (String)dht.readHumidity();
    server.send(200, "application/json", "{\"data\":" + h + "}");
}

void CustomServer::readTemperature() {
    PRINT_DEBUG("\n\tRequest Humedity\n");
    String t = (String)dht.readTemperature();
    server.send(200, "application/json", "{\"data\":" + t + "}");
}

void CustomServer::hadlerNotFound() {
    if (serveStatic(server.uri())) return;
    if (server.method() == HTTP_OPTIONS) {
      cors();
      return;
    }
    server.send(404, "application/json", "{\"msg\":\"route no found\"}");
}

bool CustomServer::serveStatic(String path) { 
    if (server.method() != HTTP_GET) return false;

    if(path.equals("/")) path += "index.html";
    String contentType = getContentType(path);

    if(SPIFFS.exists(path)){
      File file = SPIFFS.open(path, "r");    
      server.streamFile(file, contentType);
    }

    if(SPIFFS.exists(path + ".gz")){
      File file = SPIFFS.open(path + ".gz", "r");    
      server.streamFile(file, contentType);
    }
    return false;
}

String CustomServer::getContentType(String filename) {
  if(filename.endsWith(".html")) return "text/html";
  else if(filename.endsWith(".css")) return "text/css";
  else if(filename.endsWith(".js")) return "application/javascript";
  else if(filename.endsWith(".ico")) return "image/x-icon";
  else if(filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

DynamicJsonDocument CustomServer::parseBody(String str) {
  DynamicJsonDocument doc(200);
  DeserializationError err = deserializeJson(doc, str);
  
  if(err) {
    PRINT_DEBUG(F("deserializeJson() failed with code "));
    PRINT_DEBUG(err.c_str());
  }

  return doc;
}
