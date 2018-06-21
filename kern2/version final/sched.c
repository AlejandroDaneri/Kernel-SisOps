#include "decls.h"
#include "sched.h"

#define MAX_TASK 10
#define IF_FLAG 0x200

static struct Task Tasks[MAX_TASK];
static struct Task *current = NULL;

bool getFreeTask(struct Task **new_task) {
    size_t i=0;
    bool new_free_task=false;
    while ((i<MAX_TASK) && !new_free_task){
        if (Tasks[i].status == FREE){
            (*new_task) = &Tasks[i];
            new_free_task=true;
            }
        i++;
    }
    return new_free_task;
}

void sched_init() {
    size_t  i = 0;
    while (i<MAX_TASK && Tasks[i].status != READY){
        i++;
    }
    if (Tasks[i].status == READY) {
        current = &Tasks[i];
        current->status = RUNNING;
    }
}

void initialize_task(struct Task **task, void (*entry)(void)) {
    (*task)->status = READY;

    uint8_t* stack = &(*task)->stack[USTACK_SIZE] - sizeof(struct TaskFrame);
    (*task)->frame = (struct TaskFrame *)stack;

    (*task)->frame->ebp = 0;
    (*task)->frame->esp = 0;
    (*task)->frame->eax = 0;
    (*task)->frame->ebx = 0;
    (*task)->frame->ecx = 0;
    (*task)->frame->edx = 0;
    (*task)->frame->edi = 0;
    (*task)->frame->esi = 0;
    (*task)->frame->eip = (uint32_t)entry;
    (*task)->frame->cs = 0x8;
    (*task)->frame->eflags = IF_FLAG;
}

void spawn(void (*entry)(void)) {
    struct Task* new_task = NULL;
    bool success = getFreeTask(&new_task);
    if (!success)
        return;
    initialize_task(&new_task, entry);
}


static bool first_call = true;

void sched(struct TaskFrame *tf) {
    struct Task *new_task = NULL;
    struct Task *old_task = current;
    size_t task_index = 0;

    while ((task_index < MAX_TASK) && (&Tasks[task_index] != old_task)){
        task_index++;
    }

    old_task->status = READY;

    while (!new_task){
        task_index++;
        if (task_index >= MAX_TASK){
            task_index = 0;
        }
        if (Tasks[task_index].status == READY){
            new_task = &Tasks[task_index];
            if (!first_call){
                old_task->frame = tf;
            } else
                first_call = false;
            current = new_task;
            current->status = RUNNING;

            asm("movl %0, %%esp\n"
                "popa\n"
                "iret\n"
            :
            : "g"(current->frame)
            : "memory");
        }
    }
}

void kill_current_task(){
    current->status = DYING;
    halt();
}
