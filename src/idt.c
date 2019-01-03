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

    init_intr_gate(0x00, (uint32_t) timer_handler); // Registers timer_handler to IRQ 0

    /*init_idt_desc(0x08, (uint32_t) _asm_exc_GP, IDT_INTERRUPT, &kidt[13]);
    init_idt_desc(0x08, (uint32_t) _asm_exc_PF, IDT_INTERRUPT, &kidt[14]);

    init_idt_desc(0x08, (uint32_t) _asm_schedule, IDT_INTERRUPT, &kidt[32]);
    init_idt_desc(0x08, (uint32_t) _asm_int_1, IDT_INTERRUPT, &kidt[33]);

    init_idt_desc(0x08, (uint32_t) _asm_syscalls, IDT_TRAP, &kidt[48]);
    init_idt_desc(0x08, (uint32_t) _asm_syscalls, IDT_TRAP, &kidt[128]); //48*/

    /* Copy the IDT to the memory */
    memcpy((char *) IDT.base, (char *) kidt, IDT.limite);

    /* Load the IDTR registry */
    __asm__ __volatile__("lidtl (IDT)");

    // TODO init PIC
}
