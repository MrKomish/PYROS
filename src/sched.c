#include <stdint.h>
#include <stddef.h>
#include "kprint.h"

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
} task_t;

void program1() {
    kprint("A");
}

void program2() {
    kprint("B");
}

task_t tasks[MAX_TASKS] = {0};
uint32_t tasks_amount = 0;

uint8_t start_task(int (*task_code)()) {
    if (tasks_amount == MAX_TASKS) {
        return -ERR_TASK_START;
    }

    tasks[tasks_amount].pid = tasks_amount;
    tasks[tasks_amount].state = TASK_RUNNING;

    tasks_amount += 1;

    return 0;
}

task_t* current_task = NULL;

void sched_init() {

}