#
#
#

SRC_DIR = ./src
INC_DIR = ./include

#CROSS_COMPILE = /home/matsi/devel/tools/CodeSourcery/Sourcery_CodeBench_for_ARM_GNU_Linux_2012.03-47/bin/arm-none-linux-gnueabi-
CROSS_COMPILE = /home/matsi/devel/tools/CodeSourcery/2014.05-17-arm/bin/arm-none-eabi-

CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld

CFLAGS  = -g -mcpu=cortex-m3 -mthumb -I$(SRC_DIR) -I$(INC_DIR) -D GCC_ARMCM -O2 -Wall -fno-stack-protector -fno-unwind-tables -fno-exceptions
LDFLAGS = -Tcortex-m3.lds
LIBGCC  = $(shell $(CC) -mthumb -mcpu=cortex-m3 -print-libgcc-file-name)

# target: leds.out
LEDS_SRCS = startup.c main.c stdlib.c trace.c
LEDS_INCS = $(INC_DIR)/common.h $(INC_DIR)/remoteproc.h $(INC_DIR)/trace.h
LEDS_OBJS = ${LEDS_SRCS:.c=.o}

# list of targets
TARGETS = leds.out

# rules
all: $(TARGETS)

leds.out: $(LEDS_OBJS) $(LEDS_INCS) $(LIBGCC) cortex-m3.lds
	$(LD) $(LDFLAGS) $(LEDS_OBJS) $(LIBGCC) -o $@

%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f *.o $(TARGETS)

.PHONY: clean
