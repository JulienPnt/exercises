#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "ring_buffer.h"
#include "timer.h"

bool is_ring_buffer_empty(const ring_buffer my_ring_buffer) {
  if (my_ring_buffer.head == my_ring_buffer.tail) {
    return true;
  }
  return false;
}

bool is_ring_buffer_full(const ring_buffer my_ring_buffer) {
  if (my_ring_buffer.tail + 1 == my_ring_buffer.head) {
    return true;
  }
  return false;
}

uint8_t insert_uint8_t_into_ring_buffer(ring_buffer *my_ring_buffer,
                                        const timer_t *value) {
  if (is_ring_buffer_full(*my_ring_buffer)) {
    return 1;
  }
  my_ring_buffer->buffer[my_ring_buffer->tail % my_ring_buffer->size] = value;
  my_ring_buffer->tail++;
  return 0;
}

uint8_t delete_into_ring_buffer(ring_buffer *my_ring_buffer) {
  if (is_ring_buffer_empty(*my_ring_buffer)) {
    return 1;
  }
  my_ring_buffer->head++;
  return 0;
}

uint32_t get_ring_buffer_szx(const ring_buffer my_ring_buffer) {
  return (my_ring_buffer.tail - my_ring_buffer.head) % my_ring_buffer.size;
}

void display_ring_buffer(const ring_buffer my_ring_buffer) {
  printf("my_ring_buffer = { .head = %u, .tail = %u, .size = %u }\n",
         my_ring_buffer.head, my_ring_buffer.tail, my_ring_buffer.size);
  if (is_ring_buffer_empty(my_ring_buffer)) {
    printf("Selected ring buffer is empty\n");
    return;
  }
  uint32_t i = 0;
  char buffer[255];
  for (i = my_ring_buffer.head; i < my_ring_buffer.tail; i++) {
    memset(buffer, 0, 255);
    cast_timer_to_str(*my_ring_buffer.buffer[i % my_ring_buffer.size], buffer);
    printf("buffer[%u] = %s\n", (i - my_ring_buffer.head) % my_ring_buffer.size,
           buffer);
  }
  return;
}
