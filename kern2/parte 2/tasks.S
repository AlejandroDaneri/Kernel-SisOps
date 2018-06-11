.data

.text
.globl task_exec
.globl task_swap
task_exec:
    
    push %ebp
    movl %esp, %ebp

    movl 8(%ebp), %eax
    movl 12(%ebp), %esp
    call *%eax

    leave
    ret

task_swap:

