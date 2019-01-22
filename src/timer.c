/**
 * The Programmable Interval Timer (PIT) is an essential component of modern computers, especially in a multi-tasking environment.
 * The PIT chip can be made ‒ by setting various register values ‒ to count up or down, at certain rates, and to trigger interrupts at certain times.
 * The timer can be set into a cyclic mode, so that when it triggers it automatically starts counting again, or it can be set into a one-time-only countdown mode.
 * From: https://en.wikibooks.org/wiki/X86_Assembly/Programmable_Interval_Timer
 * Another Useful resource - http://kernelx.weebly.com/programmable-interval-timer.html
 *
 * Other x86 time sources include the local APIC timer and the processor’s time stamp counter (TSC) ~ Linux Kernel Development
 */

#include <stdint.h>
#include <stdbool.h>
#include "io/io.h"
#include "interrupts/idt.h"
#include "io/kprint.h"
#include "timer.h"
#include "interrupts/irq.h"
#include "init.h"

void timer_set(uint32_t freq)
{
    uint32_t divisor = PIT_FREQUENCY / freq;

    outb(PIT_CMDREG , 0x36);
    outb(PIT_CHANNEL0, (uint8_t) (divisor & 0xFF));
    outb(PIT_CHANNEL0, (uint8_t) (divisor >> 8));
}

uint64_t timer_counter = 0;

__attribute__ ((interrupt)) void timer_handler(timer_int_frame_t* frame)
{
    timer_counter++;

    call_timer_handlers(frame);
    pic_send_eoi(PIC_IRQ_TIMER);
}

void init_timer()
{
    timer_set(TIMER_FREQUENCY);
    irq_enable(PIC_IRQ_TIMER);
}

/**
 * Timer handlers
 */

timer_handler_t timer_handlers[TIMER_HANDLERS_MAX_AMOUNT] = { 0 };

size_t timer_handlers_amount = 0;

void register_timer_handler(timer_handler_t handler) {
    if (timer_handlers_amount == TIMER_HANDLERS_MAX_AMOUNT) {
        kprint("Max amount of timer handlers reached");
        kexit();
    }

    timer_handlers[timer_handlers_amount] = handler;
    timer_handlers_amount++;
}

void call_timer_handlers(timer_int_frame_t* frame) {
    for (size_t i = 0; i < timer_handlers_amount; i++) {
        timer_handlers[i](frame);
    }
}