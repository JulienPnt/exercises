#ifndef INSERTION_SORT
#define INSERTION_SORT

#include "timer.h"
#include <stdint.h>
#include <stdlib.h>

/*
 * Testing purpose
 */
uint8_t insertion_sort(uint8_t *array, const size_t size);

/* Insertion sort algorythm
 * @rg const timer's array index reference where to start the sort
 * @rg const size_t size number of index reference to sort
 * @status:
 *    - 0 in case of sucess
 *    - never returns status != 0
 */
uint8_t insertion_sort_rtime(const rtimer_t *array, const size_t size);
#endif
