#include "gdt.h"

void gdt_init() {
    gdt_descriptors[0] = create_descriptor(0, 0, 0);
    gdt_descriptors[1] = create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL0));
    gdt_descriptors[2] = create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL0));
    gdt_descriptors[3] = create_descriptor(0, 0x000FFFFF, (GDT_CODE_PL3));
    gdt_descriptors[4] = create_descriptor(0, 0x000FFFFF, (GDT_DATA_PL3));

    GDT.size = DESCRIPTORS_AMOUNT * sizeof(gdt_desc_t) - 1;
    GDT.offset = gdt_descriptors;

    gdt_flush();
}