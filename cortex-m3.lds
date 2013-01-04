ENTRY(ResetISR)

MEMORY
{
	/* The last 10K from 0xF7800 are reserved for trace buffer */
	SRAM (rwx) : ORIGIN = 0x00000, LENGTH = 990K
}

SECTIONS
{
	.text :
	{
		KEEP(*(.isr_vector));
		* (.text*);
		* (.rodata*);
		* (.init*);
		* (.fini*);
	} > SRAM

	.data : AT (ADDR(.text) + SIZEOF(.text))
	{
		* (.data);
		* (.bss);
	} > SRAM

	.resource_size :
	{
		KEEP(*(.resource_size));
	} > SRAM

	.resource_table :
	{
		KEEP(*(.resource_table));
	} > SRAM
}
