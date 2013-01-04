SRC_DIR = ./src
BUILD_DIR = ./build

CROSS_COMPILE ?= arm-angstrom-linux-gnueabi-

CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld

CFLAGS = -g -mcpu=cortex-m3 -mthumb -I$(SRC_DIR) -D GCC_ARMCM -O2 -Wall
LDFLAGS = -Tcortex-m3.lds
LIBGCC=$(shell $(CC) -mthumb -mcpu=cortex-m3 -print-libgcc-file-name)

VPATH = $(SRC_DIR)
APPLICATION_OBJS = \
	$(BUILD_DIR)/main.o \
	$(BUILD_DIR)/startup.o \
	$(BUILD_DIR)/stdlib.o

OBJS =	$(APPLICATION_OBJS)

all: demo.out

demo.out: $(OBJS) $(LIBGCC) cortex-m3.lds
	$(LD) $(LDFLAGS) $(OBJS) $(LIBGCC) -o demo.out

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c $(BUILD_DIR)
	$(CC) -c -MD $(CFLAGS) -o $@ -Wp,-MD,$(BUILD_DIR)/$*.d $<
	sed -i -e 's|.*:|$(BUILD_DIR)/$*.o:|' $(BUILD_DIR)/$*.d

clean:
	rm -f $(BUILD_DIR)/*.d
	rm -f $(BUILD_DIR)/*.o
	rm -f demo.out

.PHONY: clean
