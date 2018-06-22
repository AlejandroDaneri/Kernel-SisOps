# kernel-sisop
https://fisop.github.io/7508/lab/kern2/

## Para imprimir

https://github.com/AlejandroDaneri/kernel-sisop/blob/master/kern2/version%20final/textos/PARA_IMPRIMIR.pdf

## Tips:
 Lo que sigue se tiene que hacer sobre la terminal que levanto QEMU.
 
 Para cerrar QEMU hay que hacer Ctrl-A, soltar y después apretar la x (minúscula).
 
 Para entrar al monitor: Ctrl-A y después c . Se puede ejecutar info registers
 para ver todos los registros.
 
 **Para debuggear sobre el kernel:**
 
 Primero se debe correr make qemu-gdb en una terminal, se va a levantar qemu 
 y queda Stopped
 
 Despues hay que abrir otra terminal y correr make gdb, para empezar
  a correr el kernel se pone "c" en la terminal del gdb
