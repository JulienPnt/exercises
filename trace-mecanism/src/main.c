#include <stdio.h>

#define MODULE_ID "MY MODULE"
#include "logs.h"

int main() {
  printf("Hi!\n");
  error("test");
  warning("test");
  info("test");
  dbg("test");
  read_log();
  return 0;
}
