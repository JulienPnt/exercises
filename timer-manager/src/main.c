#include <stdint.h>
#include <stdio.h>

#include "ring_buffer.h"

#define BUFFER_SIZE 10

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
