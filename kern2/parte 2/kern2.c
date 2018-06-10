#include "decls.h"
#include "multiboot.h"

void kmain(const multiboot_info_t *mbi) {
    vga_write("kern2 loading.............", 8, 0x70);
    if(mbi){}
    two_stacks();
    /*/ equivalente en C de two_stacks()
    vga_write("vga_write() from stack1", 12, 0x17);
    vga_write("vga_write() from stack2", 13, 0x90);
    /*/
}
