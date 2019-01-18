#include <stdint.h>
#include "multiboot.h"
#include "kprint.h"

#define MAX_MEMORY_AREAS_COUNT (256)

typedef struct memory_area_t {
    uint64_t base_addr;
    uint64_t length;
} memory_area_t;

void* kernel_base_addr;
void* kernel_end_addr;
uint32_t kernel_size;

memory_area_t memory_areas[MAX_MEMORY_AREAS_COUNT];
uint16_t memory_areas_count;

void save_memory_ares(multiboot_info_t* mbd);
void kinit_memory(multiboot_info_t* mbd);
