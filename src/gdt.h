#pragma once

#include "gdtlib.h"

#ifndef PYROS_GDT_H
#define PYROS_GDT_H

#define DESCRIPTORS_AMOUNT (5)

#define GDT_CODE_KENREL SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_CODE_EXRD

#define GDT_DATA_KERNEL SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_DATA_RDWR

#define GDT_CODE_USER SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_CODE_EXRD

#define GDT_DATA_USER SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_DATA_RDWR

#define GDT_BASE_SELECTOR (0x00)
#define GDT_CODE_KERNEL_SELECTOR (GDT_BASE_SELECTOR + 0x08)
#define GDT_DATA_KERNEL_SELECTOR (GDT_CODE_KERNEL_SELECTOR + 0x08)
#define GDT_CODE_USER_SELECTOR (GDT_DATA_KERNEL_SELECTOR + 0x08)
#define GDT_DATA_USER_SELECTOR (GDT_CODE_USER_SELECTOR + 0x08)

gdt_desc_t gdt_descriptors[DESCRIPTORS_AMOUNT];

gdt_t GDT;

void gdt_init();
void gdt_flush();

#endif //PYROS_GDT_H
