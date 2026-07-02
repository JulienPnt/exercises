#include <stdint.h>
#include <stdio.h>

const volatile uint32_t hw_clock = 0;
volatile uint32_t hw_trigger = 0;

typedef void (*timer_cb)(void);
timer_cb callback = NULL;

typedef struct _scheduler scheduler;
struct _scheduler {
  uint32_t time_trigger;
  timer_cb callback;
  struct _scheduler *post;
  scheduler *pre;
};

scheduler my_scheduler[255];

void hw_trigger_isr() {
  if (callback == NULL) {
    return;
  }
  callback();
}

uint32_t read_current_time() { return hw_clock; }

uint8_t set_timer(const uint32_t duration, const timer_cb my_callback) {
  if (my_callback == NULL) {
    return 1;
  }

  hw_trigger = hw_clock + duration;

  return 0;
}

int main() {
  printf("Hi!\n");
  return 0;
}
