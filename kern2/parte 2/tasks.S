.data

.text
.globl task_exec
task_exec:
    
    push %ebp
    movl %esp, %ebp

    movl 8(%ebp), %eax
    movl 12(%ebp), %esp
    call *%eax

    leave
    ret

.globl task_swap
task_swap:
    push %ebp
    push %ebx
    push %edi
    push %esi

    movl 20(%esp), %eax

    movl %esp, %ecx
    movl (%eax), %esp
    movl %ecx, (%eax)

    pop %esi
    pop %edi
    pop %ebx
    pop %ebp

    ret