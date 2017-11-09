#include "config_mode.h"

// Tu należy podać dane dla nowego punktu dostępowego WiFi:
String ssid = "ESP_";
const char password[] = "Wilk_i_Zajac";

// Inne dane potrzebne do działania programu:
ESP8266WebServer server(80);    // Obiekt serwera HTTP.
char buf[200];                  // Bufor na tekst z pliku SPIFFS.

// FUNKCJE NIEPUBLICZNE:

// Funkcja odpowiedzialna za adres "/":
void handleRoot()
{
  if (server.args() > 0) // Jeżeli podano jakieś parametry to:
  {
    Serial.println("W zapytaniu podano parametry!");
    for (uint8_t i = 0; i < server.args(); i++)
    {
      if (server.argName(i) == "nazwa") // Jeżeli jednym z parametrów jest "nazwa" to:
      {
        Serial.print("Twoja nazwa to: ");
        Serial.println(server.arg(i)); // Wypisz wartość pola "nazwa".
      }
    }
  }
  Serial.println("Przesyłam stronę: '/'");
  server.send(200, "text/plain", buf); // Prześlij zawartość bufora (plik tekstowy) do klienta. Prześlij kod 200 (OK).
}

// FUNKCJE PUBLICZNE:

void configSetup()
{
  // Uruchom UART do debugowania:
  Serial.begin(9600);
  Serial.println("\nTRYB KONFIGURACJI");

  // Ustaw tryb AP (Tryb punktu dostępowego) i wyłącz tryb STA (Tryb stacji):
  WiFi.mode(WIFI_AP);

  // Dodaj do SSID numer MAC:
  ssid += WiFi.macAddress();

  // Utwórz punkt WiFi:
  Serial.print("Tworzenie punktu WiFi...");
  WiFi.softAP(ssid.c_str(), password);
  Serial.println(" Utworzono!");
  Serial.print("Twój adres IP: ");
  Serial.println(WiFi.softAPIP());

  // Zamontuj system plików SPIFFS:
  if (SPIFFS.begin() == true)
  {
    Serial.println("Udało się zamontować system plików!");
  }
  else
  {
    Serial.println("Nie udało się zamontować systemu plików!");
  }

  // Odczytaj zawartość pliku '/tekst' - otwórz w trybie tylko do odczytu:
  File f = SPIFFS.open("/tekst", "r");
  if (f == true)
  {
    Serial.println("Udało się otworzyć plik: '/tekst'");
  }
  else
  {
    Serial.println("Nie udało się otworzyć pliku: '/tekst");
  }
  Serial.print("Z pliku odczytano ");
  Serial.print(f.read((uint8_t*)buf, 200));
  Serial.println(" bajtów danych");

  // Zamknij plik i odmontuj system plików SPIFFS:
  f.close();
  SPIFFS.end();

  // Przypisz strony do adresów i uruchom serwer:
  server.on("/", handleRoot); // Strona główna. Adres: "/".
  server.begin();
}

void configLoop()
{
  // Zajmij się obsługiwaniem klienta:
  server.handleClient();
}

