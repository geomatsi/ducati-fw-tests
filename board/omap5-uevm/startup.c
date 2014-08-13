#include "remoteproc.h"
#include "common.h"
#include "trace.h"

#include "omap5-uevm.h"

void ResetISR(void);

static void NmiISR(void);
static void FaultISR(void);
static void DefaultISR(void);

extern int main(void);

static unsigned long Stack[STACK_SIZE];

/*
 * Describe the resources required by this firmware image.
 * Currently we simply map 1M of pyhsical memory from PA=CPU_TEXT_MEM
 * to the device address 0x0 to hold our text/data sections.
 * We also map a 1M block containing the GPIO perihperal registers (PA=CPU_GPIO_MEM)
 * to a device address IPU_GPIO_MEM so we can flash a LED.
 */

struct carveout_entry {
    unsigned int type;
    struct fw_rsc_carveout data;
};

struct devmem_entry {
    unsigned int type;
    struct fw_rsc_devmem data;
};

struct trace_entry {
    unsigned int  type;
    struct fw_rsc_trace data;
};

struct resource_table_ducati {
    unsigned int version;
    unsigned int num;
    unsigned int reserved[2];
    unsigned int offset[3];

    /* text carveout entry */
    struct carveout_entry text_cout;

    /* devmem entry */
    struct devmem_entry devmem0;

    /* trace entry */
    struct trace_entry trace;
};

__attribute__ ((section (".resource_table")))
volatile struct resource_table_ducati resources = {
    1,
    3,
    { 0 },

    {
        offsetof(struct resource_table_ducati, text_cout),
        offsetof(struct resource_table_ducati, devmem0),
        offsetof(struct resource_table_ducati, trace),
    },

    {
        RSC_CARVEOUT, { IPU_TEXT_MEM, CPU_TEXT_MEM, IPU_TEXT_SIZE, 0x0, 0, IPU_TEXT_NAME }
    },

    {
        RSC_DEVMEM, { IPU_GPIO_MEM, CPU_GPIO_MEM, IPU_GPIO_SIZE, 0x0, 0, IPU_GPIO_NAME }
    },

    {
        RSC_TRACE, { TRACE_ADDR, TRACE_SIZE, 0, TRACE_NAME }
    }
};

/* */

__attribute__ ((section(".isr_vector")))
void (* const Vectors[])(void) =
{
	(void (*)(void))((unsigned long) Stack + sizeof(Stack)),
	ResetISR,		// Reset
	NmiISR,		// Nmi
	FaultISR,		// Hard fault
	DefaultISR,	// MPU fault
	DefaultISR,	// Bus fault
	DefaultISR,	// Usage fault
	0, 0, 0, 0,
	DefaultISR,	// SVCall handler
	DefaultISR,	// Debug
	0,
	DefaultISR,	// PendSV
	DefaultISR,	// SysTick

	/* External Handlers */
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
	DefaultISR,
};

void ResetISR(void)
{
	main();
}

static void NmiISR(void)
{
	trace_append("NMI\n");

	while(1) {}
}

static void FaultISR(void)
{
	trace_append("FAULT\n");

	while(1) {}
}

static void DefaultISR(void)
{
	trace_append("ISR\n");

	while(1) { }
}
