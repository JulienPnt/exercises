#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "ring_buffer.h"
#include "timer.h"

bool is_ring_buffer_empty(const ring_buffer my_ring_buffer) {
  return (my_ring_buffer.head % my_ring_buffer.size ==
          my_ring_buffer.tail % my_ring_buffer.size);
}

bool is_ring_buffer_full(const ring_buffer my_ring_buffer) {
  return ((my_ring_buffer.tail + 1) % my_ring_buffer.size ==
          my_ring_buffer.head % my_ring_buffer.size);
}

uint32_t get_ring_buffer_szx(const ring_buffer my_ring_buffer) {
  return my_ring_buffer.tail - my_ring_buffer.head;
}

uint8_t insert_timer_into_ring_buffer(ring_buffer *my_ring_buffer,
                                      const rtimer_t value) {
  if (is_ring_buffer_full(*my_ring_buffer)) {
    return 1;
  }
  my_ring_buffer->buffer[my_ring_buffer->tail % my_ring_buffer->size]
      .trigger_timestamp = value.trigger_timestamp;
  my_ring_buffer->buffer[my_ring_buffer->tail % my_ring_buffer->size].callback =
      value.callback;
  my_ring_buffer->buffer[my_ring_buffer->tail % my_ring_buffer->size].id =
      value.id;
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

static uint8_t is_target_on_the_head(ring_buffer *my_ring_buffer,
                                     const uint32_t target_index) {
  return target_index == my_ring_buffer->head;
}

static uint8_t find_target_id(ring_buffer *my_ring_buffer,
                              const uint32_t target_id, uint32_t *index) {
  uint32_t target_index = 0;
  uint32_t i = my_ring_buffer->head;
  for (i = my_ring_buffer->head; i < my_ring_buffer->tail; i++) {
    if (my_ring_buffer->buffer[i % my_ring_buffer->size].id == target_id) {
      *index = i;
      return 0;
    }
  }

  return (target_index == 0);
}

uint8_t delete_timer_into_ring_buffer(ring_buffer *my_ring_buffer,
                                      const uint32_t target_id) {
  if (is_ring_buffer_empty(*my_ring_buffer)) {
    return 1;
  }

  uint32_t target_index = 0;
  if (find_target_id(my_ring_buffer, target_id, &target_index)) {
    return 2;
  }

  if (is_target_on_the_head(my_ring_buffer, target_index)) {
    my_ring_buffer->head++;
    return 0;
  }

  uint32_t i = 0;
  for (i = target_index; i >= my_ring_buffer->head; i--) {
    my_ring_buffer->buffer[i % my_ring_buffer->size] =
        my_ring_buffer->buffer[(i - 1) % my_ring_buffer->size];
  }
  my_ring_buffer->head++;
  return 0;
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
    cast_timer_to_str(my_ring_buffer.buffer[i % my_ring_buffer.size], buffer);
    printf("buffer[%u] = %s\n", (i - my_ring_buffer.head) % my_ring_buffer.size,
           buffer);
  }
  return;
}
