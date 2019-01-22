#pragma once

/**
 * CPU Control Registers
 * https://en.wikipedia.org/wiki/Control_register
 */

#ifndef CONTROL_H
#define CONTROL_H

#include <stdint.h>

#define CR0_PROTECTED_MODE (1) // If 1, system is in protected mode, else system is in real mode
#define CR0_MONITOR_CO_PROCESSOR (1 << 1) // Controls interaction of WAIT/FWAIT instructions with TS flag in CR0
#define CR0_EMULATION (1 << 2) // If set, no x87 floating-point unit present, if clear, x87 FPU present
#define CR0_TASK_SWITCHED (1 << 3) // Allows saving x87 task context upon a task switch only after x87 instruction used
#define CRO_EXTENSION_TYPE (1 << 4) // On the 386, it allowed to specify whether the external math coprocessor was an 80287 or 80387
#define CR0_NUMBRIC_ERROR (1 << 5) // Enable internal x87 floating point error reporting when set, else enables PC style x87 error detection
#define CR0_WRITE_PROTECT (1 << 16) // When set, the CPU can't write to read-only pages when privilege level is 0
#define CR0_ALIGNMENT_MASK (1 << 18) // Alignment check enabled if AM set, AC flag (in EFLAGS register) set, and privilege level is 3
#define CR0_NOT_WRITE_THROUGH (1 << 29) // Globally enables/disable write-through caching
#define CR0_CACHE_DISABLE (1 << 30) // Globally enables/disable the memory cache
#define CR0_PAGING_ENABLE (1 << 31) // If 1, paging enabled and uses the CR3 register, else paging disabled

typedef uint32_t cr0_value;

static inline void set_cr0(cr0_value value) {
    __asm__ __volatile__ ("mov %0, %%cr0" :: "r" (value));
}

static inline cr0_value get_cr0() {
    uint32_t value;
    __asm__ __volatile__ ("mov %%cr0, %0" : "=r" (value) :);
    return value;
}

static inline void set_page_directory(const uint32_t page_dir) {
    __asm__ __volatile__ ("mov %0, %%cr3" :: "r" (page_dir));
}

#endif //CONTROL_H