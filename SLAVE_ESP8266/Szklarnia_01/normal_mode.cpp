#include "normal_mode.h"

// Tu należy podać dane do punktu dostępowego WiFi:
const char ssid[] = "UPC3758752";
const char password[] = "ETPXYMPH";

// Inne dane potrzebne do działania programu:
static uint8_t id = 7;   // ID urządzenia.
char bufAdres[200];      // Bufor na stworzenie adresu dla HTTP.
int getReturn = 0;       // Wartość zwracana przez metodę GET.

// FUNKCJE NIEPUBLICZNE:


// FUNKCJE PUBLICZNE:

void normalSetup()
{
  // Uruchom UART do debugowania:
  Serial.begin(9600);
  Serial.println("\nTRYB NORMALNY");

  // Inicjalizuj EEPROM (tak naprawdę jest to pamięć w FLASH). Rozmiar od 4 do 4096 bajtów:
  EEPROM.begin(4);

  // Odczytaj ID SLAVE'a z pamięci EEPROM (FLASH); jako parametr read należy przekazać indeks bajtu:
  id = EEPROM.read(0);

  // Ustaw tryb STA (Tryb stacji) i wyłącz tryb AP (Tryb punktu dostępowego):
  WiFi.mode(WIFI_STA);

  // Zainicjuj połączenie WiFi:
  WiFi.begin(ssid, password);

  // Czekaj na uzyskanie połączenia i wypisz uzyskany adres IP:
  Serial.println("Łączenie z WiFi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(400);
  }
  Serial.println(" Połączono!");
  Serial.print("Twój adres IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("Rozpoczynam wysyłanie zapytań...");
}

void normalLoop()
{
  // Utwórz klienta HTTP:
  HTTPClient http;

  // Odczytaj wartość z ADC i połącz z adresem MASTER:
  sprintf(bufAdres, "http://192.168.0.162:3000/data?id=%d&value=%d", id, analogRead(0));
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

  // Sprawdź czy został wprowadzony nowy numer SLAVE'a:
  if (Serial.available() > 0)
  {
    // Odczytaj wartość int z UART, a następnie zapisz do zmiennej id oraz pamięci EEPROM:
    id = Serial.parseInt();

    // Pierwszy parametr: adres; drugi parametr: wartość.
    EEPROM.write(0, id);

    // Zatwierdź zmiany w pamięci EEPROM:
    EEPROM.commit();

    Serial.print("Wprowadzono nowy numer identyfikacyjny: ");
    Serial.println(id);
  }

  // Zakończ połączenie HTTP:
  http.end();

  delay(3000);
}

