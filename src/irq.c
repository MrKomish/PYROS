/**
 * The function of the PIC (Programmable Interrupt Controller) is to manage hardware interrupts and send them to the appropriate system interrupt.
 * Code is based on https://wiki.osdev.org/PIC and http://www.randomhacks.net/2015/11/16/bare-metal-rust-configure-your-pic-interrupts/
 * Another useful resource https://en.wikibooks.org/wiki/X86_Assembly/Programmable_Interrupt_Controller
 * Note APIC may be used instead
 */

#include "io.h"
#include "kprint.h"
#include "irq.h"

/**
 * reinitialize the PIC controllers, giving them specified vector offsets
   rather than 0x8 and 0x70, as configured by default
 * @param offset1 - vector offset for master PIC - vectors on the master become offset1..offset1+7
 * @param offset2 - same for slave PIC: offset2..offset2+7
 */
void pic_remap(uint8_t offset1, uint8_t offset2)
{
    unsigned char a1, a2;

    // Save interrupt masks.
    a1 = inb(PIC1_DATA);
    a2 = inb(PIC2_DATA);

    // Send command: Begin 3-byte initialization sequence.
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();

    // Send data 1: Set interrupt offset.
    outb(PIC1_DATA, offset1); // ICW2: Master PIC vector offset
    io_wait();
    outb(PIC2_DATA, offset2); // ICW2: Slave PIC vector offset
    io_wait();

    // Send data 2: Configure chaining.
    outb(PIC1_DATA, 4); // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    io_wait();
    outb(PIC2_DATA, 2); // ICW3: tell Slave PIC its cascade identity (0000 0010)
    io_wait();

    // Send data 3: Set mode.
    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    outb(PIC1_DATA, a1);   // restore saved masks.
    outb(PIC2_DATA, a2);
}

void init_irq() {
    pic_remap(0x20, 0x28);
}

/**
 * Send end of interrupt command
 * @param irq
 */
void pic_send_eoi(unsigned char irq)
{
    if(irq >= 8) {
        outb(PIC2_COMMAND, PIC_EOI);
    }

    outb(PIC1_COMMAND, PIC_EOI);
}

/**
 * This register is a bitmap of the request lines going into the PIC. When a bit is set, the PIC ignores the request and continues normal operation.
 * Note that setting the mask on a higher request line will not affect a lower line.
 * Masking IRQ2 will cause the Slave PIC to stop raising IRQs.
 *
 * @param IRQline - Line to mask
 */
void irq_set_mask(unsigned char IRQline) {
    port_t port;
    uint8_t value;

    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = (uint8_t) (inb(port) | (1 << IRQline));
    outb(port, value);
}

/**
 * @param IRQline - Line to unmask
 */
void irq_clear_mask(unsigned char IRQline) {
    port_t port;
    uint8_t value;

    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = (uint8_t) (inb(port) & ~(1 << IRQline));
    outb(port, value);
}

/**
 * TODO add spurious interrupts
 */