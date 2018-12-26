#include "idtlib.h"

void init_idt_desc(uint16_t selector, uint32_t offset, uint8_t type_attr, idt_desc_t *desc)
{
    desc->offset0_15 = (uint16_t) (offset & 0xffff);
    desc->selector = selector;
    desc->zero = 0;
    desc->type_attr = type_attr;
    desc->offset16_31 = (uint16_t) ((offset & 0xffff0000) >> 16);
}
