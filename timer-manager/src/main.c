#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "insertion_sort.h"
/* #ifdef UNIT_TEST*/
#include "unit_test.h"

/* #endif */

uint8_t cast_array_to_str(const uint8_t *array, const size_t szx, char **str) {
  if (array == NULL) {
    return 1;
  }
  if (szx == 0) {
    return 2;
  }
  size_t i = 0;
  *str = malloc(szx * 4 * sizeof(char));
  for (i = 0; i < szx; i++) {
    sprintf(*str + i * 4, "%.3u;", array[i]);
  }
  return 0;
}

static uint8_t setup_random_array(uint8_t *array, const size_t size,
                                  const uint8_t max) {
  srand(time(NULL));
  size_t i = 0;
  uint8_t rd_value = 0;
  for (i = 0; i < size; i++) {
    rd_value = rand() % (max + 1);
    array[i] = rd_value;
  }
  return 0;
}

#define BUFFER_SIZE 10

int main() {
  timer_ring_buffer_unit_test();
  insertion_sort_unit_test();
  return 0;
}
