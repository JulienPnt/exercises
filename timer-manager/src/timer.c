#include <stdint.h>
#include <stdio.h>

#include "timer.h"

uint8_t *cast_timer_to_str(const rtimer_t my_timer, char *buffer) {
  sprintf(buffer, "id: %.3u; trigger_timestamp: %.3u; callback: %s",
          my_timer.id, my_timer.trigger_timestamp,
          my_timer.callback ? "OK" : "KO");
  return 0;
}
