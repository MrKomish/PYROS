#include <stddef.h>
#include <stdint.h>
#include "main.h"
#include "kprint.h"
#include "idt.h"
#include "timer.h"
#include "irq.h"
#include "io.h"

void kmain() {
    term_init(); // Initiate terminal

    init_idt();
    init_irq();

    enable_interrupts();
    init_timer();

    // __asm__("int $0x80");

    // Display some messages
    kprint("Hello, World!\n");
    kprint("Welcome to the kernel.\n");
}
