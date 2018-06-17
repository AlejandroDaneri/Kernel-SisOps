#define PIC1 0x20
#define ACK_IRQ 0x20

.globl ack_irq
ack_irq:
        // Indicar que se manejó la interrupción.
        movl $ACK_IRQ, %eax
        outb %al, $PIC1
        iret


.globl breakpoint
breakpoint:
        // (1) Guardar registros.
        pusha
        // (2) Preparar argumentos de la llamada.
        // vga_write2("Hello, breakpoint", 14, 0xB0)
        movl $0xB0, %ecx
        movl $14, %edx
        movl $breakpoint_msg, %eax
        // (3) Invocar a vga_write2()
        call vga_write2
        // (4) Restaurar registros.
        popa
        // (5) Finalizar ejecución del manejador.
        iret


.globl timer_asm
timer_asm:
        // Guardar registros.
        pusha
        call timer
        // Restaurar registros.
        popa
        jmp ack_irq


.data
breakpoint_msg:
        .asciz "Hello, breakpoint"


