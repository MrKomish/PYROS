#ifndef PYROS_IRQ_H
#define PYROS_IRQ_H

#include <stdint.h>

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

#define PIC_EOI		0x20		/* End-of-interrupt command code */

#define ICW1_ICW4	0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */

#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08	/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C	/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

#define PIC_IRQ_TIMER 0
#define PIC_IRQ_KEYBOARD 1

#define irq_mask_enable(current_mask, intno) \
    ((uint16_t) ((current_mask) & ~(1 << (intno))))

#define irq_mask_disable(current_mask, intno) \
    ((uint16_t) ((current_mask) | (1 << (intno))))

#define IRQ_MASK_ENABLE_ALL_INTERRUPTS  0x0000
#define IRQ_MASK_DISABLE_ALL_INTERRUPTS 0xffff

void init_irq();
void pic_remap(uint8_t offset1, uint8_t offset2);
void pic_send_eoi(uint8_t irq);

void pic_set_mask(uint16_t mask);
uint16_t pic_get_mask();
void irq_enable(uint8_t irq_line);
void irq_disable(uint8_t irq_line);

#endif //PYROS_IRQ_H
