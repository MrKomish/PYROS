#include <stddef.h>
#include <stdint.h>
#include "main.h"
#include "kprint.h"
#include "idt.h"

void kmain() {
    init_idt();

    // Initiate terminal
    term_init();

    __asm__("int $0x80");

    // Display some messages
    kprint("Hello, World!\n");
    kprint("Welcome to the kernel.\n");
}
