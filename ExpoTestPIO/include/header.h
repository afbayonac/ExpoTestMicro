#ifndef HEADER
#define HEADER

#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include "FS.h"

#include "CustomServer.h"

#define DEBUG_NOWIRE_MONITOR

#ifdef DEBUG_NOWIRE_MONITOR

void PRINT_DEBUG (const char* str) { Serial.print(str);}
void PRINT_DEBUG (const String str) { 
    char charbuff[str.length()];
    str.toCharArray(charbuff, str.length() + 1);
    Serial.print(charbuff);
}
#else
void PRINT_DEBUG(const char* str) {};
void PRINT_DEBUG(String str) {}
#endif

void initAP();
void initmDNS();
void initServer();
void initSPIFFS();


#endif

 