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

.data
breakpoint_msg:
        .asciz "Hello, breakpoint"

