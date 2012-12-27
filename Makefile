SRC_DIR = ./src
BUILD_DIR = ./build

CROSS_COMPILE = /home/matsi/data/devel/dev-tools/angstrom-2011.03/arm/bin/arm-angstrom-linux-gnueabi-

CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS = -g -mcpu=cortex-m3 -mthumb -I$(SRC_DIR) -D GCC_ARMCM -O2 -Wall
LDFLAGS = -Tcortex-m3.lds
LIBGCC=$(shell $(CC) -mthumb -mcpu=cortex-m3 -print-libgcc-file-name)
LIBC=$(shell $(CC) -mthumb -mcpu=cortex-m3 -print-file-name=libc.a)

VPATH = $(SRC_DIR)
APPLICATION_OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/startup.o

OBJS =	$(APPLICATION_OBJS)

all: demo.bin

demo.bin: demo.out

demo.out: $(OBJS) $(LIBGCC) $(LIBC) cortex-m3.lds
	$(LD) $(LDFLAGS) $(OBJS) $(LIBGCC) $(LIBC) -o demo.out

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c $(BUILD_DIR)
	$(CC) -c -MD $(CFLAGS) -o $@ -Wp,-MD,$(BUILD_DIR)/$*.d $<
	sed -i -e 's|.*:|$(BUILD_DIR)/$*.o:|' $(BUILD_DIR)/$*.d


%.bin: %.out
	$(OBJCOPY) $< -O binary $@

clean:
	rm -f $(BUILD_DIR)/*.d
	rm -f $(BUILD_DIR)/*.o
	rm -f demo.bin demo.out

.PHONY: clean
