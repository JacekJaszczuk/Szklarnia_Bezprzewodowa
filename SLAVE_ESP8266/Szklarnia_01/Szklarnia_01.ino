#include "normal_mode.h"
#include "config_mode.h"

// Tryby działania SLAVE: tryb NORMALNY i tryb KONFIGURACJI:
enum class MODE{ NORMAL, CONFIG };
MODE mode;

void setup()
{
  // Czekaj sekundę na stabilizację wszystkich układów:
  delay(1000);
  
  // Ustaw pin 5 jako wejście z podciąganiem Vcc:
  pinMode(5, INPUT_PULLUP);

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
