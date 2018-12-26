#pragma once

#include "gdtlib.h"

#ifndef PYROS_GDT_H
#define PYROS_GDT_H

#define DESCRIPTORS_AMOUNT (5)

gdt_desc_t gdt_descriptors[DESCRIPTORS_AMOUNT] = {0};

gdt_t GDT = {0};

void gdt_init();
void gdt_flush();

#endif //PYROS_GDT_H
