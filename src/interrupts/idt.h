#pragma once

#ifndef PYROS_IDT_H
#define PYROS_IDT_H

#include <stdint.h>
#include <stddef.h>
#include "../util.h"
#include "idtlib.h"
#include "../memory/gdtlib.h"
#include "../memory/gdt.h"

#define IDTBASE 0x00000000
#define IDTSIZE 0xFF

/**
 * PYROS IDT TYPES
 * Based on the linux kernel
 * @see https://www.oreilly.com/library/view/understanding-the-linux/0596005652/ch04s04.html
 */

// An Intel interrupt gate that cannot be accessed by a User Mode process
#define IDT_INTERRUPT_GATE IDT_INTEL_INTERRUPT_GATE | IDT_KERNEL_PRIVILEGE

// An Intel trap gate that can be accessed by a User Mode process
// Used mostly for syscalls
#define IDT_SYSTEM_GATE IDT_INTEL_TRAP_GATE | IDT_USER_PRIVILEGE

// An Intel interrupt gate that can be accessed by a User Mode process
// Used mostly for syscalls
#define IDT_SYSTEM_INTERRUPT_GATE IDT_INTEL_INTERRUPT_GATE | IDT_USER_PRIVILEGE

// An Intel trap gate that cannot be accessed by a User Mode process.
// Used mostly for kernel exception handlers
#define IDT_TRAP_GATE IDT_INTEL_TRAP_GATE | IDT_KERNEL_PRIVILEGE

// An Intel task gate that cannot be accessed by a User Mode process.
#define IDT_TASK_GATE IDT_INTEL_TASK_GATE | IDT_KERNEL_PRIVILEGE

idt_t IDT;
idt_desc_t kidt[IDTSIZE];

static inline void init_intr_gate(uint8_t n, uint32_t addr) {
    init_idt_desc(GDT_CODE_KERNEL_SELECTOR, addr, IDT_INTERRUPT_GATE, &kidt[n]);
}

static inline void init_system_gate(uint8_t n, uint32_t addr) {
    init_idt_desc(GDT_CODE_KERNEL_SELECTOR, addr, IDT_SYSTEM_GATE, &kidt[n]);
}

static inline void init_system_intr_gate(uint8_t n, uint32_t addr) {
    init_idt_desc(GDT_CODE_KERNEL_SELECTOR, addr, IDT_SYSTEM_INTERRUPT_GATE, &kidt[n]);
}

static inline void init_trap_gate(uint8_t n, uint32_t addr) {
    init_idt_desc(GDT_CODE_KERNEL_SELECTOR, addr, IDT_TRAP_GATE, &kidt[n]);
}

static inline void init_task_gate(uint8_t n, uint32_t addr) {
    init_idt_desc(GDT_CODE_KERNEL_SELECTOR, addr, IDT_TASK_GATE, &kidt[n]);
}

void int_ignore();
void int_time_tick();
void int_keyboard();

void init_idt(void);

#endif //PYROS_IDT_H
