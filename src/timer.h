#ifndef PYROS_TIMER_H
#define PYROS_TIMER_H

#include <stdint.h>

uint64_t timer_counter;

void timer_set(int hz);
void timer_handler();
void init_timer();

#endif //PYROS_TIMER_H
