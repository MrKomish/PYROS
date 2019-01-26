#include <stdint.h>
#include <stddef.h>
#include "io/kprint.h"
#include "timer.h"

#define MAX_TASKS (0xff)
#define ERR_TASK_START ((uint8_t) 0x1)

/**
 * Task states
 * https://en.wikipedia.org/wiki/Process_state
 */
typedef enum task_state_t {
    TASK_RUNNING,
    TASK_SLEEPING,
    TASK_STOPPED
} task_state_t;

typedef uint32_t pid_t;

/**
 * Task
 * https://en.wikipedia.org/wiki/Process_control_block
 */
typedef struct task_t {
    pid_t pid; // Task id
    task_state_t state;
    void *next_instr; // next instruction to run address
} task_t;

/**
 * Task registers
 */
typedef struct task_regs_t {
    uint32_t eax, ebx, ecx, edx, esi, edi, esp, ebp, eip, eflags, cr3;
} task_regs_t;

int program1() {
    static uint16_t i = 0;
    while (1) {
        i++;
        if (i == 0){
            kprint("A");
        }
        //kprint("A");
    }
    return 0;
}

int program2() {
    static uint16_t j = 0;
    while (1) {
        j++;
        if (j == 0){
            kprint("B");
        }
        // kprint("B");
    }
    return 0;
}

task_t tasks[MAX_TASKS] = {0};
uint32_t tasks_amount = 0;

task_t* start_task(int (*task_code)()) {
    if (tasks_amount == MAX_TASKS) {
        return (task_t *) -ERR_TASK_START;
    }

    task_t* task = &tasks[tasks_amount];

    task->pid = tasks_amount;
    task->state = TASK_RUNNING;
    task->next_instr = task_code;

    tasks_amount += 1;

    return task;
}

uint32_t current_task_index = 0;

#define current (&tasks[current_task_index])

void next_task() {
    current_task_index++;

    if (current_task_index == tasks_amount) {
        current_task_index = 0;
    }
}

void sched(timer_int_frame_t* frame) {
    kprint("\nSWITCH\n");
    current->next_instr = frame->eip;
    next_task();
    // frame->eip = current->next_instr;
}

void sched_init() {
    register_timer_handler(sched);

    task_t* task1 = start_task(program1);
    task_t* task2 = start_task(program2);

    current_task_index = 0;
}

void sched_start() {
    __asm__ __volatile__ ("jmp *%0" :: "r"(current->next_instr):);
}