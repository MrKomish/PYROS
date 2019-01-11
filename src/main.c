#include <stddef.h>
#include <stdint.h>
#include "main.h"
#include "kprint.h"
#include "idt.h"
#include "timer.h"
#include "irq.h"
#include "io.h"
#include "sched.h"

void kmain() {
    term_init(); // Initiate terminal

    gdt_init();

    init_idt();
    init_irq();
    enable_interrupts();

    sched_init();
    init_timer();

    // Display some messages
    kprint("Hello, World!\n");
    kprint("Welcome to the kernel.\n");

    sched_start();
}
