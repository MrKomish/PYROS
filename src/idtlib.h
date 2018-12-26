#pragma once

#ifndef PYROS_IDTLIB_H
#define PYROS_IDTLIB_H

#include <stdint.h>
#include <stddef.h>
#include "util.h"

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

#define IDT_TYPE(x) ((x) & 0x01)
#define IDT_STORAGE_SEG(x) (((x) & 0x01) << 0x04) // 0 for interrupt and trap gates
#define IDT_DESC_PRIVILEGE(x) (((x) & 0x02) << 0x05) // Gate call protection. Specifies which privilege Level the calling Descriptor minimum should have.
#define IDT_PRESENT(x) (((x) & 0x01) << 0x07) // 0 for unused interrupts.

#define IDT_INTERRUPT IDT_TYPE(0b1110) | IDT_STORAGE_SEG(0) | IDT_DESC_PRIVILEGE(0b00) | IDT_PRESENT(1)
#define IDT_TRAP IDT_TYPE(0b1111) | IDT_STORAGE_SEG(0) | IDT_DESC_PRIVILEGE(0b00) | IDT_PRESENT(1)

#endif //PYROS_IDTLIB_H
