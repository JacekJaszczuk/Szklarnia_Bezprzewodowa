#include "struct_config.h"
#include "normal_mode.h"

// Dane potrzebne do działania programu:

static HTTPClient http;         // Obiekt Klienta HTTP.
static char bufAdres[200];      // Bufor na stworzenie adresu dla HTTP.
static int getReturn = 0;       // Wartość zwracana przez metodę GET.

// FUNKCJE NIEPUBLICZNE:


// FUNKCJE PUBLICZNE:

void normalSetup()
{
  // Ustaw tryb STA (Tryb stacji) i wyłącz tryb AP (Tryb punktu dostępowego):
  WiFi.mode(WIFI_STA);

  // Zainicjuj połączenie WiFi:
  WiFi.begin(config.wifi_name, config.wifi_pass);

  // Czekaj na uzyskanie połączenia i wypisz uzyskany adres IP:
  Serial.println("Łączenie z WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(200);
  }
  Serial.println(" Połączono!");
  Serial.print("Twój adres IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("Rozpoczynam wysyłanie zapytań...");
}

void normalLoop()
{
  // Odczytaj wartość z ADC i połącz z adresem MASTER:
  sprintf(bufAdres, "http://%s:3000/data?id=%d&value=%d",config.master_addr, config.flower_id, analogRead(0));
  Serial.println(bufAdres);

  // Ustaw adres do którego zostanie wysłane zapytanie:
  http.begin(bufAdres);

  // Wyślij zapytanie GET i sprawdź kod zwrócony przez serwer:
  getReturn = http.GET();
  if (getReturn == 200)
  {
    Serial.print("OK ");
    Serial.println(getReturn);
  }
  else
  {
    Serial.print("Błąd ");
    Serial.println(getReturn);
  }

  // Zakończ połączenie HTTP:
  http.end();

  // Idź spać. Po obudzeniu układ ulegnie zresetowaniu:
  ESP.deepSleep(config.flower_send_period*1000000, WAKE_RF_DEFAULT);
}

