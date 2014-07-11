#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "trace.h"

#include "omap4-panda.h"

int main(void)
{
    volatile uint32_t *GPIO_DATAOUT;
    volatile uint32_t *GPIO_OE;
    volatile uint32_t *PID_REG;

	volatile int i, j;

	/* init hardware */

	GPIO_DATAOUT = (uint32_t *) IPU_GPIO_DATAOUT;
	GPIO_OE = (uint32_t *) IPU_GPIO_OE;
    PID_REG = (uint32_t *) IPU_PID_REG;

    reset_bit(GPIO_OE, 7);
    reset_bit(GPIO_OE, 8);

    reset_bit(GPIO_DATAOUT, 7);
    set_bit(GPIO_DATAOUT, 8);

	for(j = 0; j < 6; j++) {
		for( i = 0; i < 500000; i++ );
        toggle_bit(GPIO_DATAOUT, 7);
        toggle_bit(GPIO_DATAOUT, 8);
	}

    /* if we are core1, go to sleep */

    if (read32(PID_REG) != 0) {
        asm volatile ("wfi");
    }

	/* init trace buffer */

	trace_init(RUN_LOOP);
	trace_append("Hello World\n");

	/* main */

	j = 0;

	while( 1 ) {
		for(i = 0; i < 50000; i++);
        toggle_bit(GPIO_DATAOUT, 7);
        toggle_bit(GPIO_DATAOUT, 8);
		trace_append("%d = %x\n", j, j);
		j += 1;
	}
}
