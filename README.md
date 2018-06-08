# kernel-sisop
https://fisop.github.io/7508/lab/kern2/

## Importante:
 A medida que fui haciendo los ejercicios fui tageando 
 los commits cuando terminaba, despues me di cuenta que no se
 estaban subiendo algunos .c que eran necesarios :/ . Si haces un checkout en los tags 
 vas a tener que bajarte los archivos aparte

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
