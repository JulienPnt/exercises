#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

typedef void (*timer_cb)(void);

typedef struct _timer {
  uint32_t id;
  uint32_t trigger_timestamp;
  timer_cb callback;
} timer_t;

uint8_t *cast_timer_to_str(const timer_t my_timer, char *buffer);
#endif
