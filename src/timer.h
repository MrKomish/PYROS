#ifndef PYROS_TIMER_H
#define PYROS_TIMER_H

#include <stdint.h>

uint64_t timer_counter;

typedef struct interrupt_frame {
    int errCode;
    int eip;
    int ecs;
    int flags;
} interrupt_frame;

void timer_set(uint32_t freq);
__attribute__ ((interrupt)) void timer_handler(interrupt_frame* frame);
void init_timer();

#endif //PYROS_TIMER_H