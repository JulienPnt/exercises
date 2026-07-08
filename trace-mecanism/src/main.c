#include <assert.h>
#include <stdio.h>

#define MODULE_ID "UNIT TEST"
#include "logs.h"

#define NUMBER_OF_LOGS_TO_PRODUCE 255

#define MORETHAN_40_BYTES_STR                                                  \
  "testtesttesttesttestetstetstetstesttetestetest"                             \
  "testtesttesttesttestetstetstetstesttetestetest"                             \
  "testtesttesttesttestetstetstetstesttetestetest"                             \
  "testtesttesttesttestetstetstetstesttetestetest"                             \
  "testtesttesttesttestetstetstetstesttetestetest"                             \
  "testtesttesttesttestetstetstetstesttetestetest"                             \
  "testtesttesttesttestetstetstetstesttetestetest"                             \
  "testtesttesttesttestetstetstetstesttetestetest"                             \
  "testtesttesttesttestetstetstetstesttetestetest"                             \
  "testtesttesttesttestetstetstetstesttetestetest"                             \
  "testtesttesttesttestetstetstetstesttetestetest"                             \
  "testtesttesttesttestetstetstetstesttetestetest"                             \
  "testtesttesttesttestetstetstetstesttetestetest"                             \
  "testtesttesttesttestetstetstetstesttetestetest"                             \
  "testtesttesttesttestetstetstetstesttetestetest"                             \
  "testtesttesttesttestetstetstetstesttetestetest"                             \
  "testtesttesttesttestetstetstetstesttetestetest"                             \
  "testtesttesttesttestetstetstetstesttetestetest"                             \
  "testtesttesttesttestetstetstetstesttetestetest"

int main() {
  int i = 0;
  for (i = 0; i < NUMBER_OF_LOGS_TO_PRODUCE; i++) {
    switch (i % 4) {
    case 0:
      assert(error("test") == 0);
      break;
    case 1:
      assert(info("test") == 0);
      break;
    case 2:
      assert(warning("test") == 0);
      break;
    case 3:
      assert(dbg("test") == 0);
      break;
    }
  }
  assert(write_log(NULL, 0, "test", 0, "test", "test") == 1);
  assert(write_log("test", 0, NULL, 0, "test", "test") == 1);
  assert(write_log("test", 0, "test", 0, NULL, "test") == 1);
  assert(write_log("test", 0, "test", 0, "test", NULL) == 1);
  assert(write_log(MORETHAN_40_BYTES_STR, 0, "test", 0, "test", "test") == 2);
  assert(write_log("test", 0, MORETHAN_40_BYTES_STR, 0, "test", "test") == 3);
  assert(write_log("test", 0, "test", 0, MORETHAN_40_BYTES_STR, "test") == 4);
  assert(write_log("test", 0, "test", 0, "test", MORETHAN_40_BYTES_STR) == 5);
  assert(write_log("t¨st", 0, "test", 0, "test", "test") == 6);
  assert(write_log("test", 0, "t¨st", 0, "test", "test") == 7);
  assert(write_log("test", 0, "test", 0, "t¨st", "test") == 8);
  assert(write_log("test", 0, "test", 0, "test", "t¨st") == 9);
  read_log();
  return 0;
}
