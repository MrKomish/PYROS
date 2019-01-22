#include "gdt.h"

gdt_desc_t gdt_descriptors[DESCRIPTORS_AMOUNT] = {0};
gdt_t GDT = {0};

void gdt_init() {
    gdt_descriptors[0] = create_descriptor(0, 0, 0);

    gdt_descriptors[1] = create_descriptor(0, 0x000FFFFF, (GDT_CODE_KENREL));
    gdt_descriptors[2] = create_descriptor(0, 0x000FFFFF, (GDT_DATA_KERNEL));

    gdt_descriptors[3] = create_descriptor(0, 0x000FFFFF, (GDT_CODE_USER));
    gdt_descriptors[4] = create_descriptor(0, 0x000FFFFF, (GDT_DATA_USER));

    GDT.size = DESCRIPTORS_AMOUNT * sizeof(gdt_desc_t) - 1;
    GDT.offset = gdt_descriptors;

    gdt_flush();
}