#ifndef INSERTION_SORT
#define INSERTION_SORT

#include "timer.h"
#include <stdint.h>
#include <stdlib.h>

uint8_t insertion_sort(uint8_t *array, const size_t size);
uint8_t insertion_sort_rtime(const rtimer_t *array, const size_t size);
#endif
