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
#include "ioport.h"
#include "idt.h"
#include "kprint.h"

#define PIT_FREQUENCY (1193180) // Hz

#define PIT_CHANNEL0      0x40  //PIT Channel 0's Data Register Port
#define PIT_CMDREG        0x43  //PIT Chip's Command Register Port

#define TIMER_FREQUENCY (100)

void timer_set(int hz)
{
    int divisor = PIT_FREQUENCY / hz;

    outb(PIT_CMDREG , 0x36);
    outb(PIT_CHANNEL0, (uint8_t) (divisor & 0xFF));
    outb(PIT_CHANNEL0, (uint8_t) (divisor >> 8));
}

uint64_t timer_counter = 0;

void timer_handler()
{
        kprint("HI");
    timer_counter++; // Increments the variable by 1 every interrupt fired by the PIT
}

void init_timer()
{
    timer_set(TIMER_FREQUENCY);
    init_intr_gate(0, (uint32_t) timer_handler); // Registers timer_handler to IRQ 0
}