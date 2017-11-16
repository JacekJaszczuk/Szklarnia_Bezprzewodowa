#include "struct_config.h"
#include "normal_mode.h"
#include "config_mode.h"

// Główna struktura konfiguracyjna:
Configuration config = {"0", "Kwiat", 15, "Nazwa WiFi", "Hasło WiFi", "192.168.0.1"};

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

  // Inicjalizuj pamięć EEPROM:
  EEPROM.begin(sizeof(config));

  // Jeżeli pierwszy znak to '0' to zapisz standardowe dane do EEPROM:
  if (EEPROM.read(0) == 0)
  {
    Serial.println("Pusta konfiguracja! Inicjalizacja konfiguracją standardową!");
    EEPROM.put(0, config);
    // Zatwierdź zmiany w pamięci EEPROM:
    EEPROM.commit();
  }
  else // W przeciwnym wypadku wczytaj dane z EEPROM do struktury:
  {
    Serial.println("Znaleźono konfigurację! Wczytywanie konfiguracji!");
    EEPROM.get(0, config);
  }

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
