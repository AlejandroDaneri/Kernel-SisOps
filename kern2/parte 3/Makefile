CFLAGS := -g -std=c99 -Wall -Wextra -Wpedantic
## para el kernel
CFLAGS += -m32 -O1 -ffreestanding -fasm -fno-omit-frame-pointer

## .o de .S
SRCS := $(wildcard *.S)
OBJS := $(patsubst %.S,%.o,$(SRCS))

## .o de .c
SRCS := $(wildcard *.c)
SRCS += $(wildcard lib/*.c)
OBJS += $(patsubst %.c,%.o,$(SRCS))

IP := 127.0.0.1:7508

QEMU := qemu-system-i386 -serial mon:stdio
KERN := kern2
BOOT := -kernel $(KERN) $(QEMU_EXTRA)

LIBGCC := $(shell $(CC) $(CFLAGS) -print-libgcc-file-name)


qemu: $(KERN)
	$(QEMU) $(BOOT)

qemu-gdb: $(KERN)
	$(QEMU) -kernel kern2 -S -gdb tcp:127.0.0.1:7508 $(BOOT)

gdb:
	gdb -q -s -kernel kern2 -n -ex 'target remote $(IP)'

.PHONY: qemu qemu-gdb gdb

kern2: $(OBJS)
	ld -m elf_i386 -Ttext 0x100000  $^ $(LIBGCC) -o $@
	# Verificar imagen Multiboot v1.
	grub-file --is-x86-multiboot $@

%.o: %.S
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f kern2 *.o core

.PHONY: clean
