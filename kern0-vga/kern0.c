#define VGABUF ((volatile char *) 0xB8000)

#define ROWS 25 // numero de filas de la pantalla
#define COLUMNS 80 // numero de columnas de la pantalla

typedef char int8_t;
typedef unsigned char uint8_t;

static void vga_write(const char *s, int8_t linea, uint8_t color) {
    if (linea < 0) {
        linea = ROWS + linea;
    }

    volatile char* buff = VGABUF + linea * COLUMNS * 2;
    while (*s != '\0') {
        *buff++ = *s++;
        *buff++ = color;
    }
}


void comienzo(void) {
    vga_write("kern0 loading.............", 8, 0x70);

    while (1)
            asm("hlt");
}
