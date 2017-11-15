#include "struct_config.h"
#include "normal_mode.h"
#include "config_mode.h"

// Tryby działania SLAVE: tryb NORMALNY i tryb KONFIGURACJI:
enum class MODE{ NORMAL, CONFIG };
MODE mode;

void setup()
{
  // Czekaj 200ms na stabilizację wszystkich układów:
  delay(200);
  
  // Dokonaj konfiguracji wspólnej dla wszystkich trybów:
  
  // Ustaw pin 5 jako wejście z podciąganiem Vcc:
  pinMode(5, INPUT_PULLUP);

  // Uruchom UART do debugowania:
  Serial.begin(9600);
  Serial.println("\nWSTĘPNA KONFIGURACJA");

  // Zamontuj system plików SPIFFS:
  if (SPIFFS.begin() == true)
  {
    Serial.println("Udało się zamontować system plików!");
  }
  else
  {
    Serial.println("Nie udało się zamontować systemu plików!");
  }

  // Otwórz i odczytaj zawartość konfiguracji '/struct_config.bin' - otwórz w trybie tylko do odczytu:
  File f = SPIFFS.open("/struct_config.bin", "r");
  if (f == true)
  {
    Serial.println("Udało się otworzyć plik konfiguracyjny");
  }
  else
  {
    Serial.println("Nie udało się otworzyć pliku konfiguracyjnego");
  }
  Serial.print("Z pliku odczytano ");
  Serial.print(f.read((uint8_t*)&config, sizeof(config)));
  Serial.println(" bajtów danych");

  // Zamknij plik i odmontuj system plików SPIFFS:
  f.close();
  SPIFFS.end();
  Serial.println("Zamknięto plik konfiguracyjny i odmontowano SPIFFS");

  // Jeżeli na pinie 5 jest stan wysoki to ustaw tryb NORMALNY, a jak nie to KONFIGURACJI:
  if (digitalRead(5) == HIGH)
  {
    mode = MODE::NORMAL;
  }
  else
  {
    mode = MODE::CONFIG;
  }

  // Uruchom wybrany tryb konfiguracji:
  switch (mode)
  {
    case MODE::NORMAL:
      normalSetup();
      break;
    case MODE::CONFIG:
      configSetup();
      break;
  }
}

void loop()
{
  // Uruchom wybrany tryb w pętli:
  switch (mode)
  {
    case MODE::NORMAL:
      normalLoop();
      break;
    case MODE::CONFIG:
      configLoop();
      break;
  }
}
