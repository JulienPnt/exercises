#include <assert.h>
#include <stdint.h>

/* #ifdef UNIT_TEST*/
#include "unit_test.h"

/* #endif */

#define BUFFER_SIZE 10

int main() {
  /* #ifdef UNIT_TEST*/

  timer_ring_buffer_unit_test();
  /* #endif */

  return 0;
}
