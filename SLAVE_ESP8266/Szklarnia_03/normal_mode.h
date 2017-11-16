#ifndef NORMAL_MODE_H
#define NORMAL_MODE_H

// Funkcje dla trybu NORMALNEGO działania urządzenia SLAVE.

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Funkcje do konfiguracji i działania w pętli:
void normalSetup();
void normalLoop();

#endif /* NORMAL_MODE_H */
