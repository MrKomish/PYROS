#include <stddef.h>
#include <stdint.h>
#include "main.h"
#include "kprint.h"
#include "idt.h"
#include "timer.h"

void kmain() {
    init_idt();
    term_init();

    init_timer();

    // Initiate terminal

    __asm__("int $0x80");

    // Display some messages
    kprint("Hello, World!\n");
    kprint("Welcome to the kernel.\n");
}
