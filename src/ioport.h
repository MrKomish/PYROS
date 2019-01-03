#ifndef PYROS_IOPORT_H
#define PYROS_IOPORT_H

#include <stdint.h>

typedef uint8_t port_t;

static inline void outb(port_t port, uint8_t val) {
    __asm__ __volatile__ ("outb %%al, %%dx" : : "d" (port), "a" (val));
}

static inline void outw(port_t port, uint16_t val) {
    __asm__ __volatile__ ("outw %%ax, %%dx" : : "d" (port), "a" (val));
}

static inline void outl(port_t port, uint32_t val) {
    __asm__ __volatile__ ("outl %%eax, %%dx" : : "d" (port), "a" (val));
}

#endif //PYROS_IOPORT_H
