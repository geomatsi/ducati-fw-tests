#
#
#

APPLICATION_INCLUDE_DIR = include
BUILD_DIR = build

CROSS_COMPILE = arm-none-linux-gnueabi-

CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld

CFLAGS = -mthumb -mcpu=cortex-m3 -D GCC_ARMCM  -O2 -fno-stack-protector -fno-unwind-tables -fno-exceptions

CFLAGS += \
	-I$(APPLICATION_INCLUDE_DIR) \

LDFLAGS = -Tcortex-m3.lds
LIBGCC=$(shell $(CC) -mthumb -mcpu=cortex-m3 -print-libgcc-file-name)

APPLICATION_SOURCE_DIRS = \
	src

VPATH = $(APPLICATION_SOURCE_DIRS)

COMMON_OBJS = \
	$(BUILD_DIR)/trace.o \
	$(BUILD_DIR)/stdlib.o

OMAP5_UEVM_OBJS = \
	$(BUILD_DIR)/omap5-uevm/startup.o \
	$(BUILD_DIR)/omap5-uevm/main.o

OMAP4_PANDA_OBJS = \
	$(BUILD_DIR)/omap4-panda/startup.o \
	$(BUILD_DIR)/omap4-panda/main.o

all: $(BUILD_DIR) omap5-uevm omap4-panda

omap5-uevm: $(OMAP5_UEVM_OBJS) $(COMMON_OBJS) cortex-m3.lds
	$(LD) $(LDFLAGS) $(COMMON_OBJS) $(OMAP5_UEVM_OBJS) -o leds.omap5-uevm.out

omap4-panda: $(OMAP4_PANDA_OBJS) $(COMMON_OBJS) cortex-m3.lds
	$(LD) $(LDFLAGS) $(COMMON_OBJS) $(OMAP4_PANDA_OBJS) -o leds.omap4-panda.out

$(BUILD_DIR):
	mkdir $(BUILD_DIR)
	mkdir $(BUILD_DIR)/omap5-uevm
	mkdir $(BUILD_DIR)/omap4-panda

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/omap5-uevm/%.o: board/omap5-uevm/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/omap4-panda/%.o: board/omap4-panda/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(BUILD_DIR)
	rm -f leds.*.out

.PHONY: clean
