#include <stddef.h>
#include <stdint.h>

#include "insertion_sort.h"
#include "ring_buffer.h"
#include "timer.h"
#include "unit_test.h"

const volatile uint32_t hw_clock = 0;
volatile uint32_t hw_trigger = 0;

#define BUFFER_SIZE 40
rtimer_t my_timer_buffer[BUFFER_SIZE] = {0};
ring_buffer my_ring_buffer = {0, 0, BUFFER_SIZE, my_timer_buffer};
/*
 *  MODULE - API
 */

/* Read current clock register
 * @rg void
 * return uint32_t clock register
 */
uint32_t read_current_time();

/* Insert a timer into the timer manager
 *  @rg uint32_t timer duration in seconds
 *  @rg timer_cb timer callback
 *  @id uint32_t timer id
 *  return uint8_t status:
 *    - == 0 in case of success
 *    - == 1 if duration == 0
 *    - == 2 if insertion failed due to buffer overflow
 *    buffer capacity is 40 timers in parrallel
 *    - == 3 if timer sorting failed (must never happen)
 *    - == 4 if update_hw_trigger failed (must never happen)
 */
uint8_t set_timer(const uint32_t duration, const timer_cb my_callback,
                  uint32_t *id);

/* Delete a timer into the timer manager
 * @rg timer's id to delete
 * return uint8_t status :
 * - == 0 in case of success
 * - == 1 failed to remove timer (must never happen)
 * - == 2 failed to update hw trigger (must never happen)
 */
uint8_t delete_timer(const uint32_t target_id);

/*  Update hw trigger register
 * @rg void
 * @return status:
 *   - == 0 in case of sucess
 *   - == 1 if ring buffer is empty
 */
static uint8_t update_hw_trigger() {
  if (is_ring_buffer_empty(my_ring_buffer)) {
    return 1;
  }
  hw_trigger = my_ring_buffer.buffer[my_ring_buffer.head].trigger_timestamp;
  return 0;
}

timer_cb callback = NULL;
uint32_t read_current_time() { return hw_clock; }

/* Check if ring buffer contains timer to execute
 *  @return status:
 *  - == 0 => no
 *  - == 1 => yes
 */
static uint8_t execute_head_rtimer() {
  return read_current_time() ==
         my_ring_buffer.buffer[my_ring_buffer.head].trigger_timestamp;
}

/* HW trigger interrupt function
 * 1. Pop and execute every peremted timer
 * 2. Update the next hw trigger
 * @return nothing
 */
void hw_trigger_isr() {
  rtimer_t my_timer = {0};
  while (execute_head_rtimer()) {
    pop_from_ring_buffer(&my_ring_buffer, &my_timer);
    my_timer.callback();
  }
  update_hw_trigger();
  return;
}

uint8_t set_timer(const uint32_t duration, const timer_cb my_callback,
                  uint32_t *id) {
  static uint32_t timer_id = 0;
  if (duration == 0) {
    return 1;
  }
  rtimer_t my_timer = {timer_id++, read_current_time() + duration, my_callback};
  if (insert_timer_into_ring_buffer(&my_ring_buffer, my_timer)) {
    return 2;
  }
  uint32_t szx = get_ring_buffer_szx(my_ring_buffer);
  if (insertion_sort_rtime(&my_timer_buffer[my_ring_buffer.head], szx)) {
    return 3;
  }
  if (update_hw_trigger()) {
    return 4;
  }
  return 0;
}

uint8_t delete_timer(const uint32_t target_id) {
  if (delete_timer_into_ring_buffer(&my_ring_buffer, target_id)) {
    return 1;
  }
  if (update_hw_trigger()) {
    return 2;
  }
  return 0;
}

int main() {
  timer_ring_buffer_unit_test();
  insertion_sort_unit_test();
  insertion_sort_unit_test_ring_buffer();
  return 0;
}
