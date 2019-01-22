#include <stddef.h>
#include <stdint.h>
#include "main.h"
#include "io/kprint.h"
#include "interrupts/idt.h"
#include "timer.h"
#include "interrupts/irq.h"
#include "io/io.h"
#include "sched.h"
#include "init.h"
#include "memory/mem.h"
#include "memory/paging.h"

void kmain(multiboot_info_t* mbd, uint32_t magic) {

    term_init(); // Initiate terminal

    kinit_memory(mbd);

    gdt_init();

    init_idt();
    init_irq();

    kinit_paging();

    enable_interrupts();

    sched_init();
    init_timer();

    // Display some messages
    kprint("Hello, World!\n");
    kprint("Welcome to the kernel.\n");

    sched_start();
}
