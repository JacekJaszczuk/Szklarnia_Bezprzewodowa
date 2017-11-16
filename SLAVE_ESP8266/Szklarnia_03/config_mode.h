#ifndef CONFIG_MODE_H
#define CONFIG_MODE_H

// Funkcje dla trybu KONFIGURACJI urządzenia SLAVE.

#include <string.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <FS.h>

// Funkcje do konfiguracji i działania w pętli:
void configSetup();
void configLoop();

#endif /* CONFIG_MODE_H */
