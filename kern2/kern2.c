#include "decls.h"
#include "multiboot.h"
#include "lib/string.h"

void kmain(const multiboot_info_t *mbi) {
    vga_write("kern2 loading.............", 8, 0x70);

    if (mbi->flags) {
        char buf[256] = "cmdline: ";
        char *cmdline = (void *) mbi->cmdline;
        strlcat(buf, cmdline, sizeof(buf));
        vga_write(buf, 9, 0x07);
    }
    vga_write("A", 10, 0x57);
    asm("hlt");
    vga_write("B", 11, 0x60); //solo de prueba para ver si hace el halt
}
