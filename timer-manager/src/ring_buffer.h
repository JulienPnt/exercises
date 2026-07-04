#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdbool.h>
#include <stdint.h>

#include "timer.h"

typedef struct _ring_buffer {
  uint32_t head;
  uint32_t tail;
  const uint32_t size;
  const rtimer_t **buffer;
} ring_buffer;

/* Check if ring buffer is empty.
 * @rg ring_buffer to check
 * @return true if empty otherlese false
 */
bool is_ring_buffer_empty(const ring_buffer my_ring_buffer);

/* Check if ring buffer is empty.
 * @rg ring_buffer to check
 * @return true if full otherlese false
 */
bool is_ring_buffer_full(const ring_buffer my_ring_buffer);

/* Insert timer_t* value into ring buffer
 * @rg ring_buffer into insert value
 * @rg value to insert
 * @return 0 in sucess 1 if buffer is full
 */
uint8_t insert_timer_into_ring_buffer(ring_buffer *my_ring_buffer,
                                      const rtimer_t *value);
/* Delete first in entry into ring buffer
 * @rg ring_buffer into delete entry
 * @return 0 in sucess 1 if buffer is empty
 */
uint8_t delete_into_ring_buffer(ring_buffer *my_ring_buffer);

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

#endif
