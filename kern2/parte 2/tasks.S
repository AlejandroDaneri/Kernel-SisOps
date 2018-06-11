.data

.text
.globl task_exec
task_exec:
    
    push %ebp
    movl %esp, %ebp

    movl 8(%ebp), %eax
    movl 12(%ebp), %esp
    call %eax

    leave
    ret
