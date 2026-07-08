#include "logs.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 40
log my_logs_buffer[BUFFER_SIZE] = {0};

/* ================ *
 * LOGS             *
 * ================ */

typedef struct _ring_buffer {
  uint32_t head;
  uint32_t tail;
  const uint32_t size;
  log *buffer;
} ring_buffer;

ring_buffer my_logs = {0, 0, BUFFER_SIZE, my_logs_buffer};

/* Check if ring buffer is empty.
 * @rg ring_buffer to check
 * @return boolean:
 *  - == true  => empty
 *  - == false => not(empty)
 */
static bool is_logs_buffer_empty(const ring_buffer my_ring_buffer);

/* Check if ring buffer is empty.
 * @rg ring_buffer to check
 * @return boolean:
 *  - == true  => full
 *  - == false => not(full)
 */
static bool is_logs_buffer_full(const ring_buffer my_ring_buffer);

/* Delete ring_buffer's head
 * @rg ring_buffer's reference into delete entry
 * @return uint8_t status:
 * - == 0 => OK
 * - == 1 => ring_buffer is empty
 */
static uint8_t delete_into_ring_buffer(ring_buffer *my_ring_buffer);

/* Insert log value into ring buffer
 * @rg ring_buffer's reference into insert value
 * @rg value to insert
 * @return uint8_t status:
 *  - == 0 => OK
 *  - == 1 => ring_buffer is full
 */
static uint8_t insert_log_into_ring_buffer(ring_buffer *my_ring_buffer,
                                           const log value);

/* Display ring_buffer for debugging purpose
 * @rg ring_buffer to display
 * @return nothing
 */
static void display_ring_buffer(const ring_buffer my_ring_buffer);

static uint8_t check_log_size(const log my_log);
uint8_t write_log(const char *module_name, const level level,
                  const char *filename, const uint32_t line,
                  const char *function_name, const char *msg) {

  if (module_name == NULL || filename == NULL || function_name == NULL ||
      msg == NULL) {
    return 1;
  }
  static uint32_t id = 0;
  time_t now = time(NULL);
  log my_log = {level,    id,   module_name,   now,
                filename, line, function_name, msg};
  uint8_t status = 0;
  if ((status = check_log_size(my_log))) {
    return status + 1;
  }
  status = insert_log_into_ring_buffer(&my_logs, my_log);
  id++;
  return status;
}

static uint8_t check_log_size(const log my_log) {
  if (strlen(my_log.module_name) > MODULE_NAME_MAX_SZX) {
    return 1;
  } else if (strlen(my_log.filename) > FILE_NAME_MAX_SZX) {
    return 2;
  } else if (strlen(my_log.function_name) > FUNCTION_NAME_MAX_SZX) {
    return 3;
  } else if (strlen(my_log.msg) > MSG_MAX_SZX) {
    return 4;
  }
  return 0;
}

void read_log() { return display_ring_buffer(my_logs); }

/* id; module_name time [level] filename@line:function_name "my message"*/
const char *cast_level_to_str(const level my_level) {
  switch (my_level) {
  case DBG:
    return "DBG";
  case WRN:
    return "WRN";
  case INF:
    return "INF";
  case ERR:
    return "ERR";
  default:
    return "";
  }
}

static uint8_t cast_log_to_str(const log log, char *str) {
  char buffer[40];
  struct tm *t = localtime(&log.time);
  strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", t);
  sprintf(str, "%u; %s %s [%s] %s@%u:%s\t%s", log.id, buffer, log.module_name,
          cast_level_to_str(log.level), log.filename, log.line,
          log.function_name, log.msg);
  return 0;
}

static bool is_logs_buffer_empty(const ring_buffer my_ring_buffer) {
  return (my_ring_buffer.head % my_ring_buffer.size ==
          my_ring_buffer.tail % my_ring_buffer.size);
}

static bool is_logs_buffer_full(const ring_buffer my_ring_buffer) {
  return ((my_ring_buffer.tail + 1) % my_ring_buffer.size ==
          my_ring_buffer.head % my_ring_buffer.size);
}

static uint8_t delete_into_ring_buffer(ring_buffer *my_ring_buffer) {
  if (is_logs_buffer_empty(*my_ring_buffer)) {
    return 1;
  }
  my_ring_buffer->head++;
  return 0;
}

static uint8_t insert_log_into_ring_buffer(ring_buffer *my_ring_buffer,
                                           log value) {
  if (is_logs_buffer_full(*my_ring_buffer)) {
    delete_into_ring_buffer(my_ring_buffer);
  }
  memcpy(my_ring_buffer->buffer + my_ring_buffer->tail % my_ring_buffer->size,
         &value, sizeof(log));
  my_ring_buffer->tail++;
  return 0;
}

static void display_ring_buffer(const ring_buffer my_ring_buffer) {
  printf("my_ring_buffer = { .head = %u, .tail = %u, .size = %u }\n",
         my_ring_buffer.head, my_ring_buffer.tail, my_ring_buffer.size);
  if (is_logs_buffer_empty(my_ring_buffer)) {
    printf("Selected ring buffer is empty\n");
    return;
  }
  uint32_t i = 0;
  char buffer[255];
  for (i = my_ring_buffer.head; i < my_ring_buffer.tail; i++) {
    memset(buffer, 0, 255);
    cast_log_to_str(my_ring_buffer.buffer[i % my_ring_buffer.size], buffer);
    printf("buffer[%u] = %s\n", (i - my_ring_buffer.head) % my_ring_buffer.size,
           buffer);
  }
  return;
}
