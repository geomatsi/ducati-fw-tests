#include "trace.h"

static volatile uint8_t *trace_buffer;
static volatile uint8_t *trace_current_ptr;
static uint32_t trace_current_len;
static int trace_mode;

void trace_init(int mode)
{
	trace_buffer = trace_current_ptr = (uint8_t *) TRACE_ADDR;
	trace_current_len = 0;
	trace_mode = mode;

	memset((void *) trace_buffer, 0x0, TRACE_SIZE);
}

static int printchar(int c)
{
	int pc = 0;

	switch (trace_mode) {
		case RUN_LOOP:
			if (trace_current_len == TRACE_SIZE) {
				trace_current_ptr = trace_buffer;
				trace_current_len = 0;
			}

			*trace_current_ptr++ = c;
			trace_current_len += 1;
			pc += 1;
			break;

		case RUN_ONCE:
		default:
			if (trace_current_len < TRACE_SIZE) {
				*trace_current_ptr++ = c;
				trace_current_len += 1;
				pc += 1;
			}

			break;
	}

	return pc;
}

static int printstr(const char *string)
{
	int pc = 0;

	for ( ; *string ; ++string) {
		pc += printchar(*string);
	}

	return pc;
}

static int printint(int i, int b, int sign, int letbase)
{
	uint32_t u, mu;
	int t;

	int pc = 0;

	if (i == 0) {
		pc += printchar('0');
		goto done;
	}

	if (sign && b == 10 && i < 0) {
		pc += printchar('-');
		u = -i;
	} else {
		u = i;
	}

	mu = 1;

	while (1) {
		if (u/mu < b)
			break;

		mu *= b;
	}

	while (mu) {
		t = u / mu;

		if( t >= 10 )
			t += letbase - '0' - 10;
		pc += printchar(t + '0');

		u = u % mu;
		mu /= b;
	}

done:
	return pc;
}

static int printvarg(int *varg)
{
	char scr[2];

	char *format = (char *)(*varg++);
	int pc = 0;

	for (; *format != 0; ++format) {
		if (*format == '%') {
			++format;
			if (*format == '\0')
				break;

			if (*format == '%')
				goto symbol;

			if( *format == 's' ) {
				char *s = *((char **)varg++);
				pc += printstr(s ? s : "(null)");
				continue;
			}

			if( *format == 'd' ) {
				pc += printint(*varg++, 10, 1, 'a');
				continue;
			}

			if( *format == 'x' ) {
				pc += printint(*varg++, 16, 0, 'a');
				continue;
			}

			if( *format == 'X' ) {
				pc += printint(*varg++, 16, 0, 'A');
				continue;
			}

			if( *format == 'u' ) {
				pc += printint(*varg++, 10, 0, 'a');
				continue;
			}

			if( *format == 'c' ) {
				scr[0] = *varg++;
				scr[1] = '\0';
				pc += printstr(scr);
				continue;
			}
		} else {
		symbol:
			pc += printchar(*format);
		}
	}

	return pc;
}

int trace_append(const char *format, ...)
{
	int *varg = (int *)(&format);

	return printvarg(varg);
}
