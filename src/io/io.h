#ifndef PYROS_IOPORT_H
#define PYROS_IOPORT_H

#include <stdint.h>
#include "../util.h"

typedef uint16_t port_t;

/**
 * Wait by writing to unused port 0x80
 */
static inline void io_wait() {
    __asm__ __volatile__ ( "outb %%al, $0x80" : : "a" (0) );
}

/**
 * Write byte to port
 * @param port
 * @param val
 */
static inline void outb(port_t port, uint8_t val) {
    __asm__ __volatile__ ( "outb %%al, %%dx" : : "d" (port), "a" (val));
}

/**
 * Write word to port
 * @param port
 * @param val
 */
static inline void outw(port_t port, uint16_t val) {
    __asm__ __volatile__ ( INTEL_START "outw %%dx, %%ax" INTEL_END : : "d" (port), "a" (val));
}

/**
 * Write long to port
 * @param port
 * @param val
 */
static inline void outl(port_t port, uint32_t val) {
    __asm__ __volatile__ ( INTEL_START "outl %%dx, %%eax" INTEL_END : : "d" (port), "a" (val));
}

/**
 * Read byte from port
 * @param port
 * @param val
 */
static inline uint8_t inb(port_t port) {
    uint8_t ret;
    __asm__ __volatile__ ( "inb %%dx, %%al" : "=a" (ret): "d" (port));
    return ret;
}

/**
 * Read word from port
 * @param port
 * @param val
 */
static inline uint16_t inw(port_t port) {
    uint16_t ret;
    __asm__ __volatile__ ( INTEL_START "inb %%ax, %%dx" INTEL_END : "=a" (ret): "d" (port));
    return ret;
}

/**
 * Read long from port
 * @param port
 * @param val
 */
static inline uint32_t inl(port_t port) {
    uint32_t ret;
    __asm__ __volatile__ ( INTEL_START "inl %%eax, %%dx" INTEL_END : "=a" (ret) : "d" (port));
    return ret;
}

static inline void enable_interrupts ()
{
    __asm__ __volatile__ ( INTEL_START "sti" INTEL_END );
}

static inline void disable_interrupts ()
{
    __asm__ __volatile__ ( INTEL_START "cli" INTEL_END );
}

//
///**
// * Wait by writing to unused port 0x80
// */
//static inline void io_wait() {
//    asm volatile ( "out 0x80, %%al" : : "a"(0) );
//}
//
///**
// * Write byte to port
// * @param port
// * @param val
// */
//static inline void outb(port_t port, uint8_t val) {
//    asm volatile (
//            "outb %0, %1;" :: "a"(val), "Nd"(port));
//}
//
///**
// * Write word to port
// * @param port
// * @param val
// */
//static inline void outw(port_t port, uint16_t val) {
//    asm volatile ("outb %0, %1;" :: "a"(val), "Nd"(port));
//    asm volatile ("outw dx, ax" :: "d" (port), "a" (val));
//}
//
///**
// * Write long to port
// * @param port
// * @param val
// */
//static inline void outl(port_t port, uint32_t val) {
//    asm volatile ("outl dx, eax" : : "d" (port), "a" (val));
//}
//
///**
// * Read byte from port
// * @param port
// * @param val
// */
//static inline uint8_t inb(port_t port) {
//    uint8_t ret;
//    asm volatile ("inb %0, %w1": "=a" (ret): "Nd" (port));
//    return ret;
//}
//
///**
// * Read word from port
// * @param port
// * @param val
// */
//static inline uint16_t inw(port_t port) {
//    uint16_t ret;
//    asm volatile ("inb %0, %w1": "=a" (ret): "Nd" (port));
//    return ret;
//}
//
///**
// * Read long from port
// * @param port
// * @param val
// */
//static inline uint32_t inl(port_t port) {
//    uint32_t ret;
//    asm volatile ("inl %0, %w1" : "=a" (ret) : "Nd" (port));
//    return ret;
//}
//
//static inline void enable_interrupts ()
//{
//    asm volatile ("sti");
//}
//
//static inline void disable_interrupts ()
//{
//    asm volatile ("cli");
//}

#endif //PYROS_IOPORT_H
