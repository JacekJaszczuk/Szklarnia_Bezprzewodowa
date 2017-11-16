// Struktura konfiguracujna. Jest tylko jeden taki obiekt w całym programie.
#include <stdint.h>

struct Configuration
{
  char flower_id[8];
  char flower_name[24];
  uint32_t flower_send_period;
  char wifi_name[24];
  char wifi_pass[24];
  char master_addr[24];
};

