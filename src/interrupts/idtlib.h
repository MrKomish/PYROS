#pragma once

#ifndef PYROS_IDTLIB_H
#define PYROS_IDTLIB_H

#include <stdint.h>
#include <stddef.h>
#include "../util.h"

typedef struct idt_t {

    uint16_t limite;
    uint32_t base;

} __attribute__ ((packed)) idt_t;

typedef struct idt_desc_t {

    uint16_t offset0_15;
    uint16_t selector; // a code segment selector in GDT or LDT
    uint8_t zero;      // unused, set to 0
    uint8_t type_attr; // type and attributes
    uint16_t offset16_31;

} __attribute__ ((packed)) idt_desc_t;

void init_idt_desc(uint16_t selector, uint32_t offset, uint8_t type_attr, idt_desc_t *desc);

#define IDT_TYPE(x) ((x) & 0b1111)
#define IDT_STORAGE_SEG(x) (((x) & 0b1) << 0x04) // 0 for interrupt and trap gates
#define IDT_DESC_PRIVILEGE(x) (((x) & 0b11) << 0x05) // Gate call protection. Specifies which privilege Level the calling Descriptor minimum should have.
#define IDT_PRESENT(x) (((x) & 0b1) << 0x07) // 0 for unused interrupts.

/**
 * INTEL IDT TYPES
 * @see https://www.oreilly.com/library/view/understanding-the-linux/0596005652/ch04s02.html
 */


// Interrupts are automatically disabled upon entry and reenabled upon IRET which restores the saved EFLAGS.
// Mostly issued by I/O devices
#define IDT_INTEL_INTERRUPT_GATE IDT_TYPE(0b1110) | IDT_STORAGE_SEG(0) | IDT_PRESENT(1)

// Reported immediately following the execution of the trapping instruction
// After the kernel returns control to the program, it is allowed to continue its execution with no loss of continuity.
#define IDT_INTEL_TRAP_GATE IDT_TYPE(0b1111) | IDT_STORAGE_SEG(0) | IDT_PRESENT(1)

// When an interrupt/exception occurs whose entry is a Task Gate, a task switch results. Mostly unused
#define IDT_INTEL_TASK_GATE IDT_TYPE(0b0101)| IDT_STORAGE_SEG(0) | IDT_PRESENT(1)

/**
 * PRIVILEGE IDT LEVELS
 */

#define IDT_KERNEL_PRIVILEGE IDT_DESC_PRIVILEGE(0b00)
#define IDT_USER_PRIVILEGE IDT_DESC_PRIVILEGE(0b11)

#endif //PYROS_IDTLIB_H
