#include <stddef.h>
#include <stdint.h>

#include "ring_buffer.h"
#include "timer.h"
#include "unit_test.h"

#define BUFFER_SIZE 40
rtimer_t my_timer_buffer[BUFFER_SIZE] = {0};
ring_buffer my_ring_buffer = {0, 0, BUFFER_SIZE, my_timer_buffer};
rtimer_t my_timers[BUFFER_SIZE];

int main() {
  timer_ring_buffer_unit_test();
  insertion_sort_unit_test();
  insertion_sort_unit_test_ring_buffer();
  return 0;
}
