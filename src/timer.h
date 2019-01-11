#ifndef PYROS_TIMER_H
#define PYROS_TIMER_H

#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>

#define PIT_FREQUENCY (1193180) // Hz

#define PIT_CHANNEL0      0x40  //PIT Channel 0's Data Register Port
#define PIT_CMDREG        0x43  //PIT Chip's Command Register Port

#define TIMER_FREQUENCY (100)

uint64_t timer_counter;

typedef struct timer_int_frame_t {
    uint32_t errCode;
    void* eip;
    uint32_t ecs;
    uint32_t flags;
} timer_int_frame_t;

void timer_set(uint32_t freq);
__attribute__ ((interrupt)) void timer_handler(timer_int_frame_t* frame);
void init_timer();

/**
 * Timer handlers
 */

#define TIMER_HANDLERS_MAX_AMOUNT (0xffff)
typedef void (*timer_handler_t)(timer_int_frame_t* frame);

timer_handler_t timer_handlers[TIMER_HANDLERS_MAX_AMOUNT];

size_t timer_handlers_amount;

void register_timer_handler(timer_handler_t handler);

void call_timer_handlers(timer_int_frame_t* frame);

#endif //PYROS_TIMER_H