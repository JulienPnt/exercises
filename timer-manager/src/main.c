#include <stdint.h>
#include <stdio.h>

#include "ring_buffer.h"
#include "timer.h"

#define BUFFER_SIZE 10

int main() {

  const timer_t *my_timer_buffer[BUFFER_SIZE] = {0};
  ring_buffer my_ring_buffer = {0, 0, BUFFER_SIZE, my_timer_buffer};

  timer_t my_timer_1 = {1, 123456, NULL};
  timer_t my_timer_2 = {1, 123456, NULL};

  display_ring_buffer(my_ring_buffer);
  insert_uint8_t_into_ring_buffer(&my_ring_buffer, &my_timer_1);
  display_ring_buffer(my_ring_buffer);
  insert_uint8_t_into_ring_buffer(&my_ring_buffer, &my_timer_2);
  display_ring_buffer(my_ring_buffer);
  delete_into_ring_buffer(&my_ring_buffer);
  display_ring_buffer(my_ring_buffer);
  delete_into_ring_buffer(&my_ring_buffer);
  display_ring_buffer(my_ring_buffer);

  return 0;
}
