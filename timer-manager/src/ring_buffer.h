#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdbool.h>
#include <stdint.h>

#include "timer.h"

typedef struct _ring_buffer {
  uint32_t head;
  uint32_t tail;
  const uint32_t size;
  rtimer_t *buffer;
} ring_buffer;

/* Check if ring buffer is empty.
 * @rg ring_buffer to check
 * @return boolean:
 *  - == true  => empty
 *  - == false => not(empty)
 */
bool is_ring_buffer_empty(const ring_buffer my_ring_buffer);

/* Check if ring buffer is empty.
 * @rg ring_buffer to check
 * @return boolean:
 *  - == true  => full
 *  - == false => not(full)
 */

bool is_ring_buffer_full(const ring_buffer my_ring_buffer);

/* Insert timer_t* value into ring buffer
 * @rg ring_buffer's reference into insert value
 * @rg value to insert
 * @return uint8_t status:
 *  - == 0 => OK
 *  - == 1 => ring_buffer is full
 */
uint8_t insert_timer_into_ring_buffer(ring_buffer *my_ring_buffer,
                                      const rtimer_t value);
/* Delete ring_buffer's head
 * @rg ring_buffer's reference into delete entry
 * @return uint8_t status:
 * - == 0 => OK
 * - == 1 => ring_buffer is empty
 */
uint8_t delete_into_ring_buffer(ring_buffer *my_ring_buffer);

/* Copy and delete ring_buffer's
 * @rg ring_buffer's reference into delete entry
 * @return uint8_t status:
 * - == 0 => OK
 * - == 1 => ring_buffer is empty
 */
uint8_t pop_from_ring_buffer(ring_buffer *my_ring_buffer, rtimer_t *my_timer);

/* Get ring buffer size
 * @rg ring_buffer to check
 * @return ring_buffer size
 */
uint32_t get_ring_buffer_szx(const ring_buffer my_ring_buffer);

/* Display ring_buffer for debugging purpose
 * @rg ring_buffer to display
 * @return nothing
 */
void display_ring_buffer(const ring_buffer my_ring_buffer);

/* Delete a timer into a ring buffer
 * @rg ring_buffer's reference where the timer must be removed
 * @rg target_id for the targeted timer
 * return 0 in case of sucess >0 in case of error
 *        1 -> ring buffer is emtpy
 *        2 -> timer id does not exist into ring buffer
 */
uint8_t delete_timer_into_ring_buffer(ring_buffer *my_ring_buffer,
                                      const uint32_t target_id);

#endif
