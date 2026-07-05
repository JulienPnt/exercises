#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "timer.h"

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

#define switch_value_rtimer(x, y)                                              \
  rtimer_t tmp = x;                                                            \
  cpy_rtimer(x, y);                                                            \
  cpy_rtimer(y, tmp)

uint8_t insertion_sort_rtime(rtimer_t *array, const size_t size) {
  size_t i = 0;
  for (i = 1; i < size; i++) {
    if (array[i - 1].trigger_timestamp > array[i].trigger_timestamp) {
      switch_value_rtimer(array[i - 1], array[i]);
      restart_queue;
    }
  }
  return 0;
}
