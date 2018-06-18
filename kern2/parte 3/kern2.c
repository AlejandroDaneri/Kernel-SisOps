#include "decls.h"
#include "multiboot.h"

#define USTACK_SIZE 4096

void kmain(const multiboot_info_t *mbi) {
    if (mbi) {
        vga_write("kern2 loading.............", 8, 0x70);

        int8_t linea;
        uint8_t color;

        two_stacks();
        two_stacks_c();
        contador_run();

        idt_init();
        irq_init();
        asm("int3");

        asm("div %4"
        : "=a"(linea), "=c"(color)
        : "0"(18), "1"(0xE0), "b"(0), "d"(0));

        vga_write2("Funciona vga_write2?", linea, color);


    }
    asm("hlt");
}

static uint8_t stack1[USTACK_SIZE] __attribute__((aligned(4096)));
static uint8_t stack2[USTACK_SIZE] __attribute__((aligned(4096)));

void two_stacks_c() {
    // Inicializar al *tope* de cada pila.
    uintptr_t *a = (uintptr_t*) stack1 + USTACK_SIZE;
    uintptr_t *b = (uintptr_t*) stack2 + USTACK_SIZE;

    // Preparar, en stack1, la llamada:

    *(a--) = 0x57;
    *(a--) = 15;
    *(a) = (uintptr_t) "vga_write() from stack1";

    // Preparar, en s2, la llamada:

    b -= 3;
    b[2] = 0xD0;
    b[1] = 16;
    b[0] = (uintptr_t) "vga_write() from stack2";

    task_exec((uintptr_t) vga_write, (uintptr_t) a);

    asm("movl %0, %%esp; call *%1; movl %%ebp, %%esp"
        :
        : "r"(b), "r"(vga_write));
}
