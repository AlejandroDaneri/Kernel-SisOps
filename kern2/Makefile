CFLAGS := -g -std=c99 -Wall -Wextra -Wpedantic
CFLAGS += -m32 -O1 -ffreestanding -fasm # para el kernel

SRCS := $(wildcard *.c)  # usar wildcard *.c
SRCS += $(wildcard lib/*.c)  # usar wildcard *.c
OBJS := $(patsubst %.c,%.o,$(SRCS)) # usar patsubst sobre SRCS

ENTRY := 0x100000
IP := 127.0.0.1:7508

QEMU := qemu-system-i386 -serial mon:stdio
KERN := kern2
BOOT := -kernel $(KERN) $(QEMU_EXTRA)

qemu: $(KERN)
	$(QEMU) $(BOOT)

qemu-gdb: $(KERN)
	$(QEMU) $(BOOT) -S -gdb tcp:$(IP) $(BOOT)

gdb:
	gdb -q -s $(KERN) -n -ex 'target remote $(IP)'

.PHONY: qemu qemu-gdb gdb

kern2: boot.o $(OBJS)
	ld -m elf_i386 -Ttext $(ENTRY) --entry $(ENTRY) $^ -o $@
	# Verificar imagen Multiboot v1.
	grub-file --is-x86-multiboot $@

%.o: %.S
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(KERN) *.o core

.PHONY: clean
