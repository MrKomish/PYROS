#pragma once

#ifndef PYROS_IDT_H
#define PYROS_IDT_H

#include <stdint.h>
#include <stddef.h>
#include "util.h"
#include "idtlib.h"
#include "gdtlib.h"

#define IDTBASE 0x00000000
#define IDTSIZE 0xFF

idt_t IDT = {0};

void init_idt(void)
{
    IDT.limite = IDTSIZE * 8;
    IDT.base = IDTBASE;

    idt_desc_t kidt[IDTSIZE];

    /* Init irq */
    for (size_t i = 0; i < IDTSIZE; i++) {
        init_idt_desc(0x08, (uint32_t) _asm_schedule, IDT_INTERRUPT, &kidt[i]); //
    }

    /* Vectors  0 -> 31 are for exceptions */
    init_idt_desc(0x08, (uint32_t) _asm_exc_GP, IDT_INTERRUPT, &kidt[13]);
    init_idt_desc(0x08, (uint32_t) _asm_exc_PF, IDT_INTERRUPT, &kidt[14]);

    init_idt_desc(0x08, (uint32_t) _asm_schedule, IDT_INTERRUPT, &kidt[32]);
    init_idt_desc(0x08, (uint32_t) _asm_int_1, IDT_INTERRUPT, &kidt[33]);

    init_idt_desc(0x08, (uint32_t) _asm_syscalls, IDT_TRAP, &kidt[48]);
    init_idt_desc(0x08, (uint32_t) _asm_syscalls, IDT_TRAP, &kidt[128]); //48

    /* Copy the IDT to the memory */
    memcpy((char *) IDT.base, (char *) kidt, IDT.limite);

    /* Load the IDTR registry */
    __asm__ __volatile__("lidtl (kidtr)");

    // TODO init PIC
}

#endif //PYROS_IDT_H
