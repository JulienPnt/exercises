#include <stdint.h>
#include <stdlib.h>

#include <stdio.h>

#define switch_value(x, y)                                                     \
  uint8_t tmp = x;                                                             \
  x = y;                                                                       \
  y = tmp;
/* Must restart at 1, but for loop increment i */
#define restart_queue                                                          \
  i = 1;                                                                       \
  i--;                                                                         \
  continue;

uint8_t insertion_sort(uint8_t *array, const size_t size) {
  size_t i = 0;
  for (i = 1; i < size; i++) {
    if (array[i - 1] > array[i]) {
      switch_value(array[i - 1], array[i]);
      restart_queue;
    }
  }
  return 0;
}
