#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>
#include <stdint.h>

#define STACK_SIZE 64

#define write32(ADDR, VAL)          ( *(unsigned int *)ADDR = (unsigned int)(VAL) )
#define read32(ADDR)                ( *(unsigned int *)ADDR )

#define toggle_bit(ADDR, BIT)       ( *(unsigned int *)ADDR ^= (1UL << (BIT)) )
#define reset_bit(ADDR, BIT)        ( *(unsigned int *)ADDR &= ~(1UL << (BIT)) )
#define set_bit(ADDR, BIT)          ( *(unsigned int *)ADDR |= (1UL << (BIT)) )

#endif /* COMMON_H */
