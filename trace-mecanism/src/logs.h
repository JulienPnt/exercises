#pragma once
#include <stdint.h>
#include <time.h>

typedef enum { DBG, WRN, INF, ERR } level;

/* id; module_name time [type] filename@line:function_name "my message"*/

#define MODULE_NAME_MAX_SZX 40
#define FILE_NAME_MAX_SZX 40
#define FUNCTION_NAME_MAX_SZX 40
#define MSG_MAX_SZX 162
typedef struct _logs {
  const level level;         // == 1 byte
  const uint32_t id;         // == 4 byte
  const char *module_name;   // < 40 bytes
  const time_t time;         // == 4 byte
  const char *filename;      // < 40 bytes
  const uint32_t line;       // == 4 byte
  const char *function_name; // < 40 bytes
  const char *msg;           // < 162
} log;

/* Prefere the use of the functions :
 * - error, warning, info, dbg
 * defined below.
 *
 * Create and insert a log into a ring buffer.
 * 1. Check any char* args is equal to NULL
 * 2. Check if size limit are respected cf comments on logging structure
 * 3. Check if buffer is not full, if full delete the oldest log
 * 4. Insert the new log
 * @rg module_name char* to identify the module
 * @rg level criticity level ERR -> DBG
 * @rg filename char* filename where the logging function is call
 * @rg line uint32_t file's line where the logging function is call
 * @rg logging's message
 * return status :
 *  - == 1 if (module_name/filename/function_name/msg) == NULL
 *  - == [2, 5] if (module_name/filename/function_name/msg) are oversized
 *  - == [6, 9] if no ascii caracter is used into
 * (module_name/filename/function_name/msg)
 */
uint8_t write_log(const char *module_name, const level level,
                  const char *filename, const uint32_t line,
                  const char *function_name, const char *msg);

/* Display all the logs stored into the buffer
 * return nothing
 * */
void read_log();

#ifdef MODULE_ID
#define error(msg)                                                             \
  write_log(MODULE_ID, ERR, __FILE_NAME__, __LINE__, __FUNCTION__, msg)
#define warning(msg)                                                           \
  write_log(MODULE_ID, WRN, __FILE_NAME__, __LINE__, __FUNCTION__, msg)
#define info(msg)                                                              \
  write_log(MODULE_ID, INF, __FILE_NAME__, __LINE__, __FUNCTION__, msg)
#define dbg(msg)                                                               \
  write_log(MODULE_ID, DBG, __FILE_NAME__, __LINE__, __FUNCTION__, msg)
#endif
