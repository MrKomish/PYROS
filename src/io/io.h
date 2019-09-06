#ifndef PYROS_IOPORT_H
#define PYROS_IOPORT_H

#include <stdint.h>
#include "../util.h"

typedef uint16_t port_t;

/**
 * Wait by writing to unused port 0x80
 */
static inline void io_wait() {
    asm volatile ( "outb %%al, $0x80" : : "a" (0) );
}

/**
 * Write byte to port
 * @param port
 * @param val
 */
static inline void outb(port_t port, uint8_t val) {
    asm volatile ( "outb %%al, %%dx" : : "d" (port), "a" (val));
}

/**
 * Write word to port
 * @param port
 * @param val
 */
static inline void outw(port_t port, uint16_t val) {
    asm volatile ( INTEL_START "outw %%dx, %%ax" INTEL_END : : "d" (port), "a" (val));
}

/**
 * Write long to port
 * @param port
 * @param val
 */
static inline void outl(port_t port, uint32_t val) {
    asm volatile ( INTEL_START "outl %%dx, %%eax" INTEL_END : : "d" (port), "a" (val));
}

/**
 * Read byte from port
 * @param port
 * @param val
 */
static inline uint8_t inb(port_t port) {
    uint8_t ret;
    asm volatile ( "inb %%dx, %%al" : "=a" (ret): "d" (port));
    return ret;
}

/**
 * Read word from port
 * @param port
 * @param val
 */
static inline uint16_t inw(port_t port) {
    uint16_t ret;
    asm volatile ( INTEL_START "inb %%ax, %%dx" INTEL_END : "=a" (ret): "d" (port));
    return ret;
}

/**
 * Read long from port
 * @param port
 * @param val
 */
static inline uint32_t inl(port_t port) {
    uint32_t ret;
    asm volatile ( INTEL_START "inl %%eax, %%dx" INTEL_END : "=a" (ret) : "d" (port));
    return ret;
}

static inline void enable_interrupts ()
{
    asm volatile ( INTEL_START "sti" INTEL_END );
}

static inline void disable_interrupts ()
{
    asm volatile ( INTEL_START "cli" INTEL_END );
}

#endif //PYROS_IOPORT_H
