#ifndef PYROS_IOPORT_H
#define PYROS_IOPORT_H

#include <stdint.h>

typedef uint8_t port_t;

/**
 * Wait by writing to unused port 0x80
 */
static inline void io_wait() {
    __asm__ __volatile__ ( "outb %%al, $0x80" : : "a"(0) );
}

/**
 * Write byte to port
 * @param port
 * @param val
 */
static inline void outb(port_t port, uint8_t val) {
    __asm__ __volatile__ ("outb %%al, %%dx" : : "d" (port), "a" (val));
}

/**
 * Write word to port
 * @param port
 * @param val
 */
static inline void outw(port_t port, uint16_t val) {
    __asm__ __volatile__ ("outw %%ax, %%dx" : : "d" (port), "a" (val));
}

/**
 * Write long to port
 * @param port
 * @param val
 */
static inline void outl(port_t port, uint32_t val) {
    __asm__ __volatile__ ("outl %%eax, %%dx" : : "d" (port), "a" (val));
}

/**
 * Read byte from port
 * @param port
 * @param val
 */
static inline uint8_t inb(port_t port) {
    uint8_t ret;
    __asm__ __volatile__ ("inb %w1, %0": "=a" (ret): "Nd" (port));
    return ret;
}

/**
 * Read word from port
 * @param port
 * @param val
 */
static inline uint16_t inw(port_t port) {
    uint16_t ret;
    __asm__ __volatile__ ("inb %w1, %0": "=a" (ret): "Nd" (port));
    return ret;
}

/**
 * Read long from port
 * @param port
 * @param val
 */
static inline uint32_t inl(port_t port) {
    uint32_t ret;
    __asm__ __volatile__ ("inl %w1, %0" : "=a" (ret) : "Nd" (port));
    return ret;
}

static inline void enable_interrupts ()
{
    __asm__ __volatile__ ("sti");
}

static inline void disable_interrupts ()
{
    __asm__ __volatile__ ("cli");
}

#endif //PYROS_IOPORT_H
