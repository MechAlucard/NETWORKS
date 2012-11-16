#define _DBG_C
#include "dbg.h"
#include "stdarg.h"
#include "stdio.h"
#include "sys/appio.h"
void dbg(char *format, ...)
  {
        char c[256];
va_list args;
va_start(args, format);
vsprintf(c, format, args);
va_end(args);
DBPUTS(c);
   }
