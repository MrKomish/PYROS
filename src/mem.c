#include "multiboot.h"
#include "mem.h"

memory_area_t memory_areas[MAX_MEMORY_AREAS_COUNT] = { 0 };
uint16_t memory_areas_count = 0;

void* kernel_base_addr = 0;
void* kernel_end_addr = 0;
uint32_t kernel_size = 0;

void save_memory_ares(multiboot_info_t* mbd) {
    uint32_t mb_mmap_len = mbd->mmap_length / sizeof(multiboot_memory_map_t);
    multiboot_memory_map_t* mb_mmap = (multiboot_memory_map_t*) mbd->mmap_addr;

    uint16_t i = 0;

    for (i = 0; i < mb_mmap_len; i++) {
        if (memory_areas_count == MAX_MEMORY_AREAS_COUNT) {
            kprint("Too many memory areas! Max 256");
        }

        if (mb_mmap[i].type == 1) {
            memory_areas[memory_areas_count].base_addr = mb_mmap[i].addr;
            memory_areas[memory_areas_count].length = mb_mmap[i].len;

            memory_areas_count++;
        }
    }
}

/**
 * Values from the linker script (linker.ld)
 */
extern const volatile void* kernel_base_symbol;
extern const volatile void* kernel_end_symbol;
extern const volatile void* kernel_size_symbol;

void kinit_memory(multiboot_info_t* mbd) {
    kernel_base_addr = (void *) &kernel_base_symbol;
    kernel_end_addr = (void *) &kernel_end_symbol;
    kernel_size = (uint32_t) &kernel_size_symbol;

    save_memory_ares(mbd);
}
