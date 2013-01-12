#include "remoteproc.h"
#include "common.h"
#include "trace.h"

void ResetISR(void);

static void NmiISR(void);
static void TestISR(void);
static void FaultISR(void);
static void DefaultISR(void);

extern int main(void);

static unsigned long Stack[STACK_SIZE];

/*
 * Describe the resources required by this firmware image.
 * Currently we simply map 1M of pyhsical memory from PA 0xb0000000
 * to the device address 0x0 to hold our text/data sections.
 * We also map a 1M block containing the GPIO1 perihperal registers (PA 0x4a300000)
 * to a device address 0xfff00000 so we can flash a LED.
 */

__attribute__ ((section(".resource_table")))
struct resource_table resources = {
	1, 3, {0}
};

__attribute__ ((section(".resource_table")))
u32 offset[] = {
	sizeof(struct resource_table) + 3*sizeof(u32),
	sizeof(struct resource_table) + 3*sizeof(u32) + sizeof(struct fw_rsc_hdr) + sizeof(struct fw_rsc_carveout),
	sizeof(struct resource_table) + 3*sizeof(u32) + sizeof(struct fw_rsc_hdr) + sizeof(struct fw_rsc_carveout) + sizeof(struct fw_rsc_hdr) + sizeof(struct fw_rsc_devmem),
};

__attribute__ ((section(".resource_table")))
struct fw_rsc_hdr carve_out = {
	RSC_CARVEOUT,
};

__attribute__ ((section(".resource_table")))
struct fw_rsc_carveout carve_out_data = {
	0, 0xb0000000, 0x100000, 0x0, 0, "text"
};

__attribute__ ((section(".resource_table")))
struct fw_rsc_hdr devmem = {
	RSC_DEVMEM,
};

__attribute__ ((section(".resource_table")))
struct fw_rsc_devmem devmem_data = {
	0xfff00000, 0x4a300000, 0x100000, 0x0, 0, "gpio1"
};

__attribute__ ((section(".resource_table")))
struct fw_rsc_hdr trace = {
	RSC_TRACE,
};

// FIXME: TRACE_ADDR = 0x100000 - TRACE_SIZE + 1

__attribute__ ((section(".resource_table")))
struct fw_rsc_trace trace_data = {
	TRACE_ADDR, TRACE_SIZE, 0, "trace"
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
	while(1) {}
}

static void FaultISR(void)
{
	while(1) {}
}

static void DefaultISR(void)
{
	while(1) {}
}

static void TestISR(void)
{
	volatile int *GPIO1_DATAOUT = (int *) 0xfff1013c;
	volatile int *GPIO1_OE = (int *) 0xfff10134;

	volatile int i;

	*GPIO1_OE &= ~(1 << 7);

	while(1) {
		for( i = 0; i < 10000; i++ );
		*GPIO1_DATAOUT ^= (1 << 7);
	}
}
