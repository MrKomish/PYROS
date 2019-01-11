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

    pic_set_mask(IRQ_MASK_DISABLE_ALL_INTERRUPTS);
}

void init_irq() {
    pic_remap(0x20, 0x28);
}

/**
 * Send end of interrupt command
 * @param irq
 */
void pic_send_eoi(uint8_t irq)
{
    if(irq >= 8) {
        outb(PIC2_COMMAND, PIC_EOI);
        io_wait();
    }

    outb(PIC1_COMMAND, PIC_EOI);
    io_wait();
}

/**
 * This register is a bitmap of the request lines going into the PIC. When a bit is set, the PIC ignores the request and continues normal operation.
 * Note that setting the mask on a higher request line will not affect a lower line.
 * Masking IRQ2 will cause the Slave PIC to stop raising IRQs.
 *
 * @param IRQline - Line to mask
 */
void pic_set_mask(uint16_t mask) {
    outb(PIC1_DATA, (uint8_t) (mask & 0xff));
    io_wait();
    outb(PIC2_DATA, (uint8_t) (mask >> 8));
    io_wait();
}

uint16_t pic_get_mask()
{
    return inb(PIC1_DATA) | (inb(PIC2_DATA) << 8);
}

void irq_enable(uint8_t irq) {
    uint16_t intmask = pic_get_mask();
    intmask = irq_mask_enable(intmask, irq);
    pic_set_mask(intmask);
}

void irq_disable(uint8_t irq) {
    uint16_t intmask = pic_get_mask();
    intmask = irq_mask_disable(intmask, irq);
    pic_set_mask(intmask);
}

/**
 * TODO add spurious interrupts
 */