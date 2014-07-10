#ifndef TRACE_H
#define TRACE_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

/* */

#define TRACE_SIZE  10240
#define TRACE_ADDR  0xf7800
#define TRACE_NAME  "trace"

enum {
	RUN_LOOP,
	RUN_ONCE,
};

/* */

void trace_init(int mode);
int trace_append(const char *fmt, ...);

#endif /* TRACE_H */
