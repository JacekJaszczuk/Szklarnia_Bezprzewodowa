// Struktura konfiguracujna. Jest tylko jeden taki obiekt w całym programie.
#include <stdint.h>

struct
{
  char flower_id[8];
  char flower_name[24];
  uint32_t flower_send_period;
  char wifi_name[24];
  char wifi_pass[24];
  char master_addr[24];
} config = {"0", "Kwiat", 15, "Nazwa WiFi", "Hasło WiFi", "192.168.0.1"};

