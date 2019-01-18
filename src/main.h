#pragma once

#ifndef PYROS_MAIN_H
#define PYROS_MAIN_H

#if defined(__linux__)
#error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
#error "This code must be compiled with an x86-elf compiler"
#endif

#include "multiboot.h"

void kmain(multiboot_info_t* mbd, uint32_t magic);

#endif //PYROS_MAIN_H
