#ifndef OMAP5_UEVM_H
#define OMAP5_UEVM_H

#define IPU_PID_REG         0xE00FFFE0

#define CPU_TEXT_MEM        0xb0000000
#define CPU_GPIO_MEM        0x4a300000

#define IPU_TEXT_MEM        0x0
#define IPU_TEXT_SIZE       0x100000
#define IPU_TEXT_NAME       "text"

#define IPU_GPIO_MEM        0xfff00000
#define IPU_GPIO_SIZE       0x100000
#define IPU_GPIO_NAME       "gpio1"

/* GPIO1 registers mapped to IPU memory */

#define IPU_GPIO_DATAOUT    0xfff1013c
#define IPU_GPIO_OE         0xfff10134

#endif /* OMAP5_UEVM_H */
