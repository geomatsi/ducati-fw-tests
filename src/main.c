#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "trace.h"

volatile uint32_t *GPIO1_DATAOUT;
volatile uint32_t *GPIO1_OE;

int main(void)
{
	volatile int i, j;

	/* init hardware */

	GPIO1_DATAOUT = (uint32_t *) 0xfff1013c;
	GPIO1_OE = (uint32_t *) 0xfff10134;

	*GPIO1_OE &= ~(1 << 7);
	*GPIO1_OE &= ~(1 << 8);

	*GPIO1_DATAOUT &= ~(1 << 7);
	*GPIO1_DATAOUT &= ~(1 << 8);

	for(j = 0; j < 6; j++) {
		for( i = 0; i < 500000; i++ );
		*GPIO1_DATAOUT ^= (1 << 8);
	}

	/* init trace buffer */

	trace_init(RUN_LOOP);
	trace_append("Hello World\n");

	/* main */

	*GPIO1_DATAOUT |= (1 << 7);
	*GPIO1_DATAOUT &= ~(1 << 8);

	j = 0;

	while( 1 ) {
		for(i = 0; i < 50000; i++);
		*GPIO1_DATAOUT ^= (1 << 7);
		*GPIO1_DATAOUT ^= (1 << 8);
		trace_append("%d = %x\n", j, j);
		j += 1;
	}
}
