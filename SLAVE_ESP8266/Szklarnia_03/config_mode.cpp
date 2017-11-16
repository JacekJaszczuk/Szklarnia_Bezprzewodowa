#include "struct_config.h"
#include "config_mode.h"

// Zdefiniuj wielkość bufora stron HTML:
#define HTML_BUF_SIZE 4000

// Dane potrzebne do działania programu:
extern Configuration config;                    // Konfiguracja z pliku głównego.
static ESP8266WebServer server(80);             // Obiekt serwera HTTP.
static char buf_A[HTML_BUF_SIZE];               // Bufor na stronę HTML z pliku SPIFFS.
static char buf_B[HTML_BUF_SIZE];               // Bufor na sformatowaną przez sprintf() stronę HTML.
static String ssid = "ESP_";                    // Nazwa tworzonej sieci WiFi.
static const char password[] = "Szklarnia";     // Hasło do tworzonej sieci WiFi.

// FUNKCJE NIEPUBLICZNE:

// Funkcja odpowiedzialna za adres "/":
void handleRoot()
{
  if (server.args() > 0) // Jeżeli podano jakieś parametry to:
  {
    Serial.println("W zapytaniu podano parametry!");

    // Przeiteruj się po wszystkich parametrach i zapisz je w odpowiednim miejscu w strukturze 'config':
    for (uint8_t i = 0; i < server.args(); i++)
    {
      if (server.argName(i) == "flower_id")
      {
        server.arg(i).toCharArray(config.flower_id, sizeof(config.flower_id));
      }
      else if (server.argName(i) == "flower_name")
      {
        server.arg(i).toCharArray(config.flower_name, sizeof(config.flower_name));
      }
      else if (server.argName(i) == "flower_send_period")
      {
        config.flower_send_period = server.arg(i).toInt();
      }
      else if (server.argName(i) == "wifi_name")
      {
        server.arg(i).toCharArray(config.wifi_name, sizeof(config.wifi_name));
      }
      else if (server.argName(i) == "wifi_pass")
      {
        server.arg(i).toCharArray(config.wifi_pass, sizeof(config.wifi_pass));
      }
      else if (server.argName(i) == "master_addr")
      {
        server.arg(i).toCharArray(config.master_addr, sizeof(config.master_addr));
      }
    }

    // Zapisz zmiany w pamięci EEPROM:
    Serial.println("Zapisywanie zmian w EEPROM!");
    EEPROM.put(0, config);

    // Zatwierdź zmiany w pamięci EEPROM:
    EEPROM.commit();
  }

  // Sformatuj i prześlij stronę:
  Serial.println("Przesyłam stronę: '/'");
  sprintf(buf_B, buf_A,
    WiFi.macAddress().c_str(),
    config.flower_name,
    WiFi.macAddress().c_str(),
    config.flower_name,
    config.flower_id,
    config.flower_name,
    config.flower_send_period,
    config.wifi_name,
    config.wifi_pass,
    config.master_addr);
  // Prześlij zawartość bufora 'buf_B' do klienta. Prześlij kod 200 (OK).
  server.send(200, "text/html", buf_B); 
}

// FUNKCJE PUBLICZNE:

void configSetup()
{
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
    Serial.println("Udało się zamontować system plików! Przygotowanie do wczytania strony WWW...");
  }
  else
  {
    Serial.println("Nie udało się zamontować systemu plików! Nie udało się przygotować do wczytania strony WWW");
  }

  // Odczytaj zawartość pliku '/config.html' - otwórz w trybie tylko do odczytu:
  File f = SPIFFS.open("/config.html", "r");
  if (f == true)
  {
    Serial.println("Udało się otworzyć plik: '/config.html'");
  }
  else
  {
    Serial.println("Nie udało się otworzyć pliku: '/config.html");
  }
  Serial.print("Z pliku odczytano ");
  Serial.print(f.read((uint8_t*)buf_A, sizeof(buf_A)));
  Serial.println(" bajtów danych");

  // Zamknij plik i odmontuj system plików SPIFFS:
  f.close();
  SPIFFS.end();
  Serial.println("Zamknięto plik strony WWW i odmontowano SPIFFS");

  // Przypisz strony do adresów i uruchom serwer:
  server.on("/", handleRoot); // Strona główna. Adres: "/".
  server.begin();
}

void configLoop()
{
  // Zajmij się obsługiwaniem klienta:
  server.handleClient();
}

