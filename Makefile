#
#
#

SRC_DIR = ./src
INC_DIR = ./include

CROSS_COMPILE ?= arm-angstrom-linux-gnueabi-

CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld

CFLAGS  = -g -mcpu=cortex-m3 -mthumb -I$(SRC_DIR) -I$(INC_DIR) -D GCC_ARMCM -O2 -Wall
LDFLAGS = -Tcortex-m3.lds
LIBGCC  = $(shell $(CC) -mthumb -mcpu=cortex-m3 -print-libgcc-file-name)

# target: leds.out
LEDS_SRCS = startup.c main.c stdlib.c
LEDS_INCS = $(INC_DIR)/common.h $(INC_DIR)/remoteproc.h
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
