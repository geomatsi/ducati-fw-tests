#ifndef OMAP5_UEVM_H
#define OMAP5_UEVM_H

#define IPU_PID_REG         0xE00FFFE0

#define CPU_TEXT_MEM        0xb0000000
#define CPU_GPIO_MEM        0x48050000

#define IPU_TEXT_MEM        0x0
#define IPU_TEXT_SIZE       0x100000
#define IPU_TEXT_NAME       "text"

#define IPU_GPIO_MEM        0xfff00000
#define IPU_GPIO_SIZE       0x10000
#define IPU_GPIO_NAME       "gpio5"

/* GPIO5 registers mapped to IPU memory */

#define IPU_GPIO_DATAOUT    0xfff0B13c
#define IPU_GPIO_OE         0xfff0B134

#endif /* OMAP5_UEVM_H */
