#include "idtlib.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"

idt_t IDT = {0};
idt_desc_t kidt[IDTSIZE] = {0};

void init_idt(void) {
    IDT.limite = IDTSIZE * 8;
    IDT.base = IDTBASE;

    /* Init irq */
    for (uint8_t i = 0; i < IDTSIZE; i++) {
        init_intr_gate(i, (uint32_t) int_ignore);
    }

    init_intr_gate(0x20, (uint32_t) timer_handler);

    /* Copy the IDT to the memory */
    memcpy((char *) IDT.base, (char *) kidt, IDT.limite);

    /* Load the IDTR registry */
    __asm__ __volatile__("lidtl (IDT)");
}
