#include "ring_buffer.h"
#include "timer.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 10
static void setup_timers(rtimer_t *my_timers) {
  time_t current_time = time(NULL);
  int i = 0;
  for (i = 0; i < BUFFER_SIZE; i++) {
    my_timers[i].id = i;
    my_timers[i].trigger_timestamp = current_time + rand() % 60 * 24;
    my_timers[i].callback = NULL;
  }
  return;
}

static void make_it_full(ring_buffer *my_ring_buffer, rtimer_t my_timers[]) {
  const uint32_t to_add =
      my_ring_buffer->size - get_ring_buffer_szx(*my_ring_buffer) - 1;
  uint32_t i = 0;
  for (i = 0; i < to_add; i++)
    assert(insert_timer_into_ring_buffer(my_ring_buffer, &my_timers[i]) == 0);
  assert(insert_timer_into_ring_buffer(my_ring_buffer, &my_timers[i]) == 1);
}

static void make_it_empty(ring_buffer *my_ring_buffer) {
  const uint32_t to_remove = get_ring_buffer_szx(*my_ring_buffer);
  uint32_t i = 0;
  for (i = 0; i < to_remove; i++)
    assert(delete_into_ring_buffer(my_ring_buffer) == 0);
  assert(delete_into_ring_buffer(my_ring_buffer) == 1);
}

void timer_ring_buffer_unit_test() {
  const rtimer_t *my_timer_buffer[BUFFER_SIZE] = {0};
  ring_buffer my_ring_buffer = {0, 0, BUFFER_SIZE, my_timer_buffer};

  rtimer_t my_timers[BUFFER_SIZE];
  setup_timers(my_timers);
  int i = 0;
  for (i = 0; i < 3; i++)
    assert(insert_timer_into_ring_buffer(&my_ring_buffer, &my_timers[i]) == 0);
  make_it_empty(&my_ring_buffer);
  make_it_full(&my_ring_buffer, my_timers);
  make_it_empty(&my_ring_buffer);
  for (i = 0; i < 7; i++)
    assert(insert_timer_into_ring_buffer(&my_ring_buffer, &my_timers[i]) == 0);
  make_it_empty(&my_ring_buffer);
  return;
}
