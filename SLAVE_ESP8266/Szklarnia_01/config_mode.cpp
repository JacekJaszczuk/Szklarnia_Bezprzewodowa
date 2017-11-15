#include "config_mode.h"

// Tu należy podać dane dla nowego punktu dostępowego WiFi:
String ssid = "ESP_";
const char password[] = "Wilk_i_Zajac";

// Inne dane potrzebne do działania programu:
static uint8_t id;              // ID urządzenia.
ESP8266WebServer server(80);    // Obiekt serwera HTTP.
char buf_A[2000];               // Bufor na tekst z pliku SPIFFS.
char buf_B[2000];               // Bufor na sformatowany przez sprintf() tekst.

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
  if (server.hasArg("ID_SLAVE"))
  {
    Serial.print("Zmiana adresu SLAVE\n");
    
    // Pierwszy parametr: adres; drugi parametr: wartość.
    EEPROM.write(0, *(server.arg("ID_SLAVE").c_str()));

    // Zatwierdź zmiany w pamięci EEPROM:
    EEPROM.commit();

    // Przeczytaj id:
    id = EEPROM.read(0);
  }
  Serial.println("Przesyłam stronę: '/'");
  sprintf(buf_B, buf_A, WiFi.macAddress().c_str(), WiFi.macAddress().c_str(), id);
  server.send(200, "text/html", buf_B); // Prześlij zawartość bufora (plik tekstowy) do klienta. Prześlij kod 200 (OK).
}

// FUNKCJE PUBLICZNE:

void configSetup()
{
  // Uruchom UART do debugowania:
  Serial.begin(9600);
  Serial.println("\nTRYB KONFIGURACJI");

  // Inicjalizuj EEPROM (tak naprawdę jest to pamięć w FLASH). Rozmiar od 4 do 4096 bajtów:
  EEPROM.begin(4);

  // Odczytaj ID SLAVE'a z pamięci EEPROM (FLASH); jako parametr read należy przekazać indeks bajtu:
  id = EEPROM.read(0);

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

  // Odczytaj zawartość pliku '/strona2.html' - otwórz w trybie tylko do odczytu:
  File f = SPIFFS.open("/strona2.html", "r");
  if (f == true)
  {
    Serial.println("Udało się otworzyć plik: '/strona2.html'");
  }
  else
  {
    Serial.println("Nie udało się otworzyć pliku: '/strona2.html");
  }
  Serial.print("Z pliku odczytano ");
  Serial.print(f.read((uint8_t*)buf_A, 2000));
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

