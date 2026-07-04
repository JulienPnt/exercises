#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define BUFFER_SIZE 10
typedef struct _ring_buffer {
  uint32_t head;
  uint32_t tail;
  const uint32_t size;
  uint8_t *buffer;
} ring_buffer;

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
                                        const uint8_t value) {
  if (is_ring_buffer_full(*my_ring_buffer)) {
    return 1;
  }
  my_ring_buffer->buffer[my_ring_buffer->tail % BUFFER_SIZE] = value;
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
  return (my_ring_buffer.tail - my_ring_buffer.head) % BUFFER_SIZE;
}

void display_ring_buffer(const ring_buffer my_ring_buffer) {
  printf("my_ring_buffer.head = %u\n", my_ring_buffer.head);
  printf("my_ring_buffer.tail= %u\n", my_ring_buffer.tail);
  printf("my_ring_buffer.size= %u\n", my_ring_buffer.size);
  if (is_ring_buffer_empty(my_ring_buffer)) {
    printf("Selected ring buffer is empty\n");
    return;
  }
  uint32_t i = 0;
  for (i = my_ring_buffer.head; i < my_ring_buffer.tail; i++) {
    printf("buffer[%u] = %u\n", (i - my_ring_buffer.head) % BUFFER_SIZE,
           my_ring_buffer.buffer[i % BUFFER_SIZE]);
  }
  return;
}

int main() {

  uint8_t buffer[BUFFER_SIZE] = {0};
  ring_buffer my_ring_buffer = {0, 0, BUFFER_SIZE, buffer};
  display_ring_buffer(my_ring_buffer);
  int i = 0;
  for (i = 0; i < 10; i++) {
    if (insert_uint8_t_into_ring_buffer(&my_ring_buffer, i)) {
      printf("Is full !\n");
    }
  }
  display_ring_buffer(my_ring_buffer);
  delete_into_ring_buffer(&my_ring_buffer);
  display_ring_buffer(my_ring_buffer);
  return 0;
}
