#include "decls.h"

/**
 * Handler para el timer (IRQ0). Escribe un carácter cada segundo.
 */
static const uint8_t hz_ratio = 18;  // Default IRQ0 freq (18.222 Hz).

#define RELEASE_CODE 0x80
#define PROMPT_CURSOR '^'
#define MAX_SIZE 81
#define SPACE ' '
#define LEFT_SHIFT 42
#define RIGHT_SHIFT 54
#define BACKSPACE '\b'
#define SIMPLE_QUOTATION_MARK '\''
#define ENTER '\n'
#define ENIE 164


void timer() {
	static char chars[MAX_SIZE];
	static unsigned ticks;
	static int8_t line = 21;
	static uint8_t idx = 0;

	if (++ticks % hz_ratio == 0) {
		chars[idx] = '.';
		chars[++idx] = '\0';
		vga_write(chars, line, 0x07);
	}

	if (idx >= sizeof(chars) - 1) {
		line++;
		idx = 0;
	}
}

/**
 * Mapa de "scancodes" a caracteres ASCII en un teclado QWERTY.
 */
static unsigned char klayout[128] = {
    //0-9
	0,   0,   '1', '2', '3', '4', '5', '6', '7', '8',
    //10-19
	'9', '0', 0,   0, BACKSPACE, 0, 'q', 'w', 'e', 'r',
    //20-29
	't', 'y', 'u', 'i', 'o', 'p', '[', ']',   ENTER,   0,
    //30-40
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ENIE, SIMPLE_QUOTATION_MARK,
    //41-50
	0, 0,   0,   'z', 'x', 'c', 'v', 'b', 'n', 'm',
    //51-60
    ',', '.', '_', 0, 0, 0, SPACE, 0,0,0};

static const uint8_t KBD_PORT = 0x60;

static bool is_shift_pressed(uint8_t scancode) {

	bool released = scancode & RELEASE_CODE;
	scancode &= ~RELEASE_CODE;

	static bool pressed;
	if (scancode == RIGHT_SHIFT || scancode == LEFT_SHIFT) {
		pressed = !released;
	}
	return pressed;
}

/**
 * Handler para el teclado (IRQ1).
 *
 * Imprime la letra correspondiente por pantalla.
 */
void keyboard() {
	uint8_t code;
    static uint8_t actual_index = 0;
	static unsigned char kbd_line[MAX_SIZE];
    static unsigned char indicator_index[MAX_SIZE];

	asm volatile("inb %1,%0" : "=a"(code) : "n"(KBD_PORT));

    int8_t offset = is_shift_pressed(code)? -32 : 0;

	if (code >= sizeof(klayout) || !klayout[code])
		return;

	kbd_line[actual_index] = klayout[code] + offset;
	vga_write((char*)kbd_line, 19, 0x0A);

    indicator_index[actual_index] = SPACE;
	indicator_index[++actual_index] = PROMPT_CURSOR;
	vga_write((char*)indicator_index, 20, 0x0C);
}
