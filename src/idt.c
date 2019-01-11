#include "idtlib.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "kprint.h"
#include "irq.h"

idt_t IDT = {0};
idt_desc_t kidt[IDTSIZE] = {0};

/*
__attribute__ ((interrupt)) void keyboard_handler(interrupt_frame* frame)
{
    kprint("KEYBOARD");

    pic_send_eoi(PIC_IRQ_KEYBOARD);
}
*/

void init_idt(void) {
    IDT.limite = IDTSIZE * 8;
    IDT.base = IDTBASE;

    /* Init irq */
    for (uint8_t i = 0; i < IDTSIZE; i++) {
        init_intr_gate(i, (uint32_t) int_ignore);
    }

    init_intr_gate(0x20, (uint32_t) timer_handler);
    //init_intr_gate(0x21, (uint32_t) keyboard_handler);

    /* Copy the IDT to the memory */
    memcpy((char *) IDT.base, (char *) kidt, IDT.limite);

    /* Load the IDTR registry */
    __asm__ __volatile__("lidtl (IDT)");
}
