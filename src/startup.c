#include <stdint.h>

/* Not static so it can be used as the entry point */
void ResetISR(void);
static void NmiISR(void);
static void FaultISR(void);
static void DefaultISR(void);

extern int main(void);

#define STACK_SIZE 64
static unsigned long Stack[STACK_SIZE];

/* ---------------------------------------------------------
   These definitions come from <linux/remoteproc.h> and
   may change as the remote processor interface is updated.
   Make sure they match the ones used by your current kernel
   source.
   ---------------------------------------------------------
*/
typedef uint32_t u32;
typedef uint64_t u64;
typedef uint8_t u8;

#define __packed __attribute__ ((packed))

struct resource_table {
  u32 ver;
  u32 num;
  u32 reserved[2];
  u32 offset[0];
} __packed;

struct fw_rsc_hdr {
  u32 type;
  u8 data[0];
} __packed;

struct fw_rsc_carveout {
  u32 da;
  u32 pa;
  u32 len;
  u32 flags;
  u32 memregion;
  u8 name[32];
} __packed;

struct fw_rsc_devmem {
  u32 da;
  u32 pa;
  u32 len;
  u32 flags;
  u32 memregion;
  u8 name[32];
} __packed;

enum fw_resource_type {
	RSC_CARVEOUT	= 0,
	RSC_DEVMEM	= 1,
	RSC_TRACE	= 2,
	RSC_VDEV	= 3,
	RSC_SUSPD_TIME	= 4,
	RSC_CUSTOM	= 5,
	RSC_LAST	= 6,
};

/* --------------------------------------------------------- */

/*
 * Describe the resources required by this firmware image.  Currently
 * we simply map 1M of pyhsical memory from PA 0xb0000000 to the device
 * address 0x0 to hold our text/data sections.  We also map a 1M block
 * containing the GPIO1 perihperal registers (PA 0x4a300000) to a device
 * address 0xfff00000 so we can flash a LED.
 */

__attribute__ ((section(".resource_table")))
struct resource_table resources = {
  1, 2, {0}
};

__attribute__ ((section(".resource_table")))
u32 offset[] = {sizeof(struct resource_table) + 2*sizeof(u32), sizeof(struct resource_table) + 2*sizeof(u32) + sizeof(struct fw_rsc_hdr) + sizeof(struct fw_rsc_carveout)};

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

/* */

__attribute__ ((section(".isr_vector")))
void (* const Vectors[])(void) =
{
  (void (*)(void))((unsigned long) Stack + sizeof(Stack)),  // Initial stack pointer
  ResetISR,  // Reset
  NmiISR,    // Nmi
  FaultISR,  // Hard fault
  DefaultISR,  // MPU fault
  DefaultISR,  // Bus fault
  DefaultISR,  // Usage fault
  0,
  0,
  0,
  0,
  DefaultISR,  // SVCall handler
  DefaultISR,  //Debug
  0,
  DefaultISR,  // PendSV
  DefaultISR,  // SysTick

  /* Vendor Handlers */
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
