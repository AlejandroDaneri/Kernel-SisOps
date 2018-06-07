#include "decls.h"
#include "lib/string.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static size_t int_width(uint64_t val) {
    // ...
}

bool fmt_int(uint64_t val, char *s, size_t bufsize) {
    size_t l = int_width(val);

    if (l >= bufsize)  // Pregunta: ¿por qué no "l > bufsize"?
        return false;

    s += l;
    // ...
    return true;
}

void print_mbinfo(const struct multiboot_info *mbi){
    char mem[256] = "Physical memory: ";
    char tmp[64] = "";

    if (fmt_int(42, tmp, sizeof tmp)) { //cambiar el 42
        strlcat(mem, tmp, sizeof mem);
        strlcat(mem, "MiB total", sizeof mem);
    }

// ...

    vga_write(mem, 10, 0x07);
}
