# Purpose
Design a trace module into an embedded system (without OS) running several tasks over a sequencer.
* Each task can log into the module.
* When a failure is detected, assertion code displays the most recent logging history.

# Requirements

Logging module :
* must be mono threaded and mono process (no OS)
* able to log during the whole system life
* limited in memory consumption
* store the most recent logging history
* provide informations to quickly to :
  * locate the log
  * measure its interest

# Specifications

## C-API

The C API is made of 4 function.

```
read_log -> to read the most recent logging history
error(msg) -> to insert an error log
warning(msg) -> to write a warning log
info(msg) -> to insert a info log
dbg(msg) -> to insert a debug log
```

> /!\ To call error/warning/info/dbg the calling script must declare a `MODULE_ID` before to include `log.h`.


```C
#define MODULE_ID "MY MODULE"
#include "logs.h"

int main() {
   dbg("test")
}

```
## Trace format

Some trace examples are shared belowed:
```
216; 08-07-2026 19:44:14 UNIT TEST [ERR] main.c@34:main     test
217; 08-07-2026 19:44:14 UNIT TEST [INF] main.c@37:main     test
218; 08-07-2026 19:44:14 UNIT TEST [WRN] main.c@40:main     test
219; 08-07-2026 19:44:14 UNIT TEST [DBG] main.c@43:main     test
220; 08-07-2026 19:44:14 UNIT TEST [ERR] main.c@34:main     test
```

Each trace is made of :
- an id -> an uint32_t value increasing at each log insertion
- a timestamp -> timestamping the log insertion
- a module id -> to identify in which module the log has been call
- a level :
  - DBG -> DEBUG (LESS CRITICAL)
  - WRN -> WARNING
  - INF -> INFO
  - ERR -> ERROR (MOST CRITICAL)
- a filename -> where the logging function has been called
- a line -> where the logging function is called
- a msg -> the logging's message



# Architecture

##  Memory

The module is using a ring buffer in fifo first in first out to store the logs.
The fifo keeps the most recent logging history using a static memory size.
At each insertion the module check if :
1. logging size respects the sized defined in `log.h` and only contains ascii caracter
2. the buffer is not full
If condition 1 failed, the insertion is aborted.
If condition 2 failed, the oldest log is deleted to insert the new one.

## Concurency

Tasks are running one after the other, no concurency mecanism seems to be required.

# Improvements

> Use a variadic implementation to do a real logging with format "value = %d", value.
