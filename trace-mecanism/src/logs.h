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

uint8_t write_log(const char *module_name, const level level,
                  const char *filename, const uint32_t line,
                  const char *function_name, const char *msg);
void read_log();

#ifdef MODULE_ID
#define error(msg)                                                             \
  write_log(MODULE_ID, ERR, __FILE_NAME__, __LINE__, __FUNCTION__, msg);
#define warning(msg)                                                           \
  write_log(MODULE_ID, WRN, __FILE_NAME__, __LINE__, __FUNCTION__, msg);
#define info(msg)                                                              \
  write_log(MODULE_ID, INF, __FILE_NAME__, __LINE__, __FUNCTION__, msg);
#define dbg(msg)                                                               \
  write_log(MODULE_ID, DBG, __FILE_NAME__, __LINE__, __FUNCTION__, msg);
#endif
