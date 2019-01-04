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
#include "io.h"
#include "idt.h"
#include "kprint.h"
#include "timer.h"
#include "irq.h"


#define PIT_FREQUENCY (1193180) // Hz

#define PIT_CHANNEL0      0x40  //PIT Channel 0's Data Register Port
#define PIT_CMDREG        0x43  //PIT Chip's Command Register Port

#define TIMER_FREQUENCY (100)

void timer_set(uint32_t freq)
{
    uint32_t divisor = PIT_FREQUENCY / freq;

    outb(PIT_CMDREG , 0x36);
    outb(PIT_CHANNEL0, (uint8_t) (divisor & 0xFF));
    outb(PIT_CHANNEL0, (uint8_t) (divisor >> 8));
}

uint64_t timer_counter = 0;

__attribute__ ((interrupt)) void timer_handler(interrupt_frame* frame)
{
    kprint("HI");
    timer_counter++;

    pic_send_eoi(0);
}

void init_timer()
{
    timer_set(TIMER_FREQUENCY);
    irq_clear_mask(PIC_IRQ_TIMER);
}