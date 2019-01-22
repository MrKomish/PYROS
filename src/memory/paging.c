#include "paging.h"

void map_tables(uint16_t dir_i, uint16_t table_start_i, uint16_t table_end_i, uint32_t base_phys_page_addr,
                uint32_t table_flags) {
    for (uint16_t page_i = table_start_i; page_i < table_end_i; page_i++) {

        page_table_t *table = &kernel_page_tables[dir_i][page_i];

        *table = table_flags | ((uint32_t) base_phys_page_addr + (page_i - table_start_i) * PAGE_SIZE);
    }
}

void map_directories(uint16_t dir_start_i, uint16_t dir_end_i, uint16_t base_phys_dir_i, uint32_t dir_flags,
                     uint32_t table_flags) {
    for (uint16_t dir_i = dir_start_i; dir_i < dir_end_i; dir_i++) {
        page_dir_t *dir = &kernel_page_dirs[dir_i];

        *dir = dir_flags | ((uint32_t) &kernel_page_tables[dir_i]);

        map_tables(dir_i, 0, PAGE_DIRECTORY_TABLES_AMOUNT,
                   ((uint32_t) base_phys_dir_i + (dir_i - dir_start_i)) * PAGE_DIRECTORY_TABLES_AMOUNT * PAGE_SIZE,
                   table_flags);
    }
}

/**
 * Identity map 0x00000000 - 0x3fffffff -> 0x00000000 - 0x3fffffff
 */
void init_kernel_paging() {
    uint16_t kernel_directory_start_i = 0x00000000 >> 22;
    uint16_t kernel_directory_end_i = 0x3fffffff >> 22;

    map_directories(
            kernel_directory_start_i, kernel_directory_end_i, 0,
            PAGE_DIRECTORY_PRESENT(1) | PAGE_DIRECTORY_WRITABLE(1),
            PAGE_TABLE_PRESENT(1) | PAGE_TABLE_WRITABLE(1)
    );

    map_directories(
            (uint16_t) (kernel_directory_end_i + 1), 0xffffffff >> 22, 0,
            PAGE_DIRECTORY_PRESENT(0), PAGE_TABLE_PRESENT(0)
    );

}

void enable_paging() {
    init_kernel_paging();

    set_page_directory((const uint32_t) kernel_page_dirs);
    set_cr0(get_cr0() | CR0_PAGING_ENABLE);
}

void kinit_paging() {
    k_base_physical_page_addr = (((uint32_t) kernel_base_addr) / PAGE_SIZE) * PAGE_SIZE;
    k_end_physical_page_addr = (((uint32_t) kernel_end_addr) / PAGE_SIZE) * PAGE_SIZE;

    enable_paging();
}