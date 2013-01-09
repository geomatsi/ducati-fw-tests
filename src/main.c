#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

volatile uint32_t *GPIO1_DATAOUT;
volatile uint32_t *GPIO1_OE;

volatile uint8_t *trace;

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

	trace = (uint8_t *) 0xf7800;
	memset((void *) trace, 0x0, TRACE_SIZE);

	trace[0] = 'a';
	trace[1] = 'b';
	trace[2] = 'c';
	trace[3] = 'd';
	trace[4] = '\n';

	/* main */

	*GPIO1_DATAOUT |= (1 << 7);
	*GPIO1_DATAOUT &= ~(1 << 8);

	while( 1 ) {
		for( i = 0; i < 100000; i++ );
		*GPIO1_DATAOUT ^= (1 << 7);
		*GPIO1_DATAOUT ^= (1 << 8);
	}
}
