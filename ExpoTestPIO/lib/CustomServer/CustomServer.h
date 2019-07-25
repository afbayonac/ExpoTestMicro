#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <FS.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 12     // Pin donde está conectado el sensor

//#define DHTTYPE DHT11   // Descomentar si se usa el DHT 11
#define DHTTYPE DHT22   // Sensor DHT22

class CustomServer {
private:
    ESP8266WebServer server = {80};
    DHT dht = {DHTPIN, DHTTYPE};
    void hadlerNotFound();
    void cors();
    void readHumidity();
    void readTemperature();
    bool serveStatic(String path);
    String getContentType(String path);
    void (* PRINT_DEBUG)(const String str);
    DynamicJsonDocument parseBody(String str);
public:
    CustomServer();
    void begin(void (* DEBUG)(const String str));
    void handle();
    ~CustomServer();
};


