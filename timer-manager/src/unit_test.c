#include "insertion_sort.h"
#include "ring_buffer.h"
#include "timer.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include <stdio.h>
/*
 * RING BUFFER
 */
#define BUFFER_SIZE 10
static void setup_timers(rtimer_t *my_timers) {
  time_t current_time = time(NULL);
  srand(current_time);
  int i = 0;
  for (i = 0; i < BUFFER_SIZE; i++) {
    my_timers[i].id = i;
    my_timers[i].trigger_timestamp = current_time + rand() % 60 * 24;
    my_timers[i].callback = NULL;
  }
  return;
}

static void make_it_full(ring_buffer *my_ring_buffer, rtimer_t my_timers[]) {
  const uint32_t to_add =
      my_ring_buffer->size - get_ring_buffer_szx(*my_ring_buffer) - 1;
  uint32_t i = 0;
  for (i = 0; i < to_add; i++)
    assert(insert_timer_into_ring_buffer(my_ring_buffer, &my_timers[i]) == 0);
  assert(insert_timer_into_ring_buffer(my_ring_buffer, &my_timers[i]) == 1);
}

static void make_it_empty(ring_buffer *my_ring_buffer) {
  const uint32_t to_remove = get_ring_buffer_szx(*my_ring_buffer);
  uint32_t i = 0;
  for (i = 0; i < to_remove; i++)
    assert(delete_into_ring_buffer(my_ring_buffer) == 0);
  assert(delete_into_ring_buffer(my_ring_buffer) == 1);
}

void timer_ring_buffer_unit_test() {
  const rtimer_t *my_timer_buffer[BUFFER_SIZE] = {0};
  ring_buffer my_ring_buffer = {0, 0, BUFFER_SIZE, my_timer_buffer};

  rtimer_t my_timers[BUFFER_SIZE];
  setup_timers(my_timers);
  int i = 0;
  for (i = 0; i < 3; i++)
    assert(insert_timer_into_ring_buffer(&my_ring_buffer, &my_timers[i]) == 0);
  make_it_empty(&my_ring_buffer);
  make_it_full(&my_ring_buffer, my_timers);
  make_it_empty(&my_ring_buffer);
  for (i = 0; i < 7; i++)
    assert(insert_timer_into_ring_buffer(&my_ring_buffer, &my_timers[i]) == 0);
  make_it_empty(&my_ring_buffer);

  make_it_full(&my_ring_buffer, my_timers);

  assert(delete_timer_into_ring_buffer(&my_ring_buffer, 0) == 0);
  assert(delete_timer_into_ring_buffer(&my_ring_buffer, 0) == 2);
  assert(delete_timer_into_ring_buffer(&my_ring_buffer, 8) == 0);
  assert(delete_timer_into_ring_buffer(&my_ring_buffer, 8) == 2);
  assert(delete_timer_into_ring_buffer(&my_ring_buffer, 4) == 0);
  assert(delete_timer_into_ring_buffer(&my_ring_buffer, 4) == 2);
  make_it_empty(&my_ring_buffer);
  assert(delete_timer_into_ring_buffer(&my_ring_buffer, 4) == 1);

  return;
}

/*
 *  INSERTION SORT - uint8_t
 */

static uint8_t setup_random_array(uint8_t *array, const size_t size,
                                  const uint8_t max);
static int is_sorted(const uint8_t *array, const size_t size);

void insertion_sort_unit_test() {

  uint8_t array[BUFFER_SIZE] = {0};
  int i = 0;
  for (i = 0; i < 40; i++) {
    setup_random_array(array, BUFFER_SIZE, 20);
    insertion_sort(array, BUFFER_SIZE);
    assert(is_sorted(array, BUFFER_SIZE) == 1);
  }
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

static int is_sorted(const uint8_t *array, const size_t size) {

  if (array == NULL) {
    return -1;
  } else if (size == 0) {
    return -2;
  }

  if (size == 1) {
    return true;
  }

  size_t i = 0;
  bool is_increasing = array[1] > array[0];
  for (i = 1; i < size; i++) {
    if (is_increasing && array[i - 1] > array[i]) {
      return false;
    } else if (!is_increasing && array[i - 1] < array[i]) {
      return false;
    }
  }
  return true;
}

/*
 *  INSERTION SORT - overt timer ring_buffer
 */

static int is_sorted_ring_buffer(const rtimer_t **array, const size_t size);

void insertion_sort_unit_test_ring_buffer() {

  const rtimer_t *my_timer_buffer[BUFFER_SIZE] = {0};
  ring_buffer my_ring_buffer = {0, 0, BUFFER_SIZE, my_timer_buffer};

  rtimer_t my_timers[BUFFER_SIZE];

  int i = 0;
  for (i = 0; i < 40; i++) {
    setup_timers(my_timers);
    make_it_full(&my_ring_buffer, my_timers);
    insertion_sort_rtime(my_ring_buffer.buffer, BUFFER_SIZE - 1);
    assert(is_sorted_ring_buffer(my_ring_buffer.buffer, BUFFER_SIZE - 1));
  }
}

static int is_sorted_ring_buffer(const rtimer_t **array, const size_t size) {

  if (array == NULL) {
    return -1;
  } else if (size == 0) {
    return -2;
  }

  if (size == 1) {
    return true;
  }

  size_t i = 0;
  bool is_increasing =
      array[1]->trigger_timestamp > array[0]->trigger_timestamp;
  for (i = 1; i < size; i++) {
    if (is_increasing &&
        array[i - 1]->trigger_timestamp > array[i]->trigger_timestamp) {
      return false;
    } else if (!is_increasing &&
               array[i - 1]->trigger_timestamp < array[i]->trigger_timestamp) {
      return false;
    }
  }
  return true;
}
