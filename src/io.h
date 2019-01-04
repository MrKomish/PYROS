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

static inline uint8_t inb(port_t port) {
    uint8_t ret;
    __asm__ __volatile__ ("inb %1, %0 ": "=a"(ret) : "Nd"(port) );
    return ret;
}

static inline uint16_t inw(port_t port) {
    uint16_t ret;
    __asm__ __volatile__ ("inb %1, %0 ": "=a"(ret) : "Nd"(port) );
    return ret;
}

static inline uint32_t inl(port_t port) {
    uint32_t ret;
    __asm__ __volatile__ ("inb %1, %0 ": "=a"(ret) : "Nd"(port) );
    return ret;
}

static inline void io_wait() {
    __asm__ __volatile__ ( "outb %%al, $0x80" : : "a"(0) );
}

#endif //PYROS_IOPORT_H
