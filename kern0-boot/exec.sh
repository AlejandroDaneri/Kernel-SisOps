# Para levantar el kernel en el QEMU

# Compilar C y ASM
gcc -g -m32 -O1 -c kern0.c boot.S

# Enlazar
ld -m elf_i386 -e0x100000  -Ttext 0x100000 kern0.o boot.o -o kern0

# Lanzar
qemu-system-i386 -serial mon:stdio -kernel kern0

# Para cerrar QEMU hay que hacer Ctrl-A, soltar y después apretar la x (minúscula)
