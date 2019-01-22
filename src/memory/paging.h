#pragma once

#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>
#include "mem.h"
#include "../control.h"

/**
 * https://wiki.osdev.org/Paging
 * http://www.renyujie.net/articles/article_ca_x86_5.php
 */

#define PAGE_DIRECTORIES_AMOUNT (1024)
#define PAGE_DIRECTORY_TABLES_AMOUNT (1024)
#define PAGE_SIZE (4096)

#define PAGE_DIRECTORY_PRESENT(x) (x)
#define PAGE_DIRECTORY_WRITABLE(x) ((x) << 1)
#define PAGE_DIRECTORY_USER_ACCESSIBLE(x) ((x) << 2)
#define PAGE_DIRECTORY_WRITE_THROUGH(x) ((x) << 3)
#define PAGE_DIRECTORY_CACHE_DISABLED(x) ((x) << 4)
#define PAGE_DIRECTORY_ACCESSED(x) ((x) << 5)
#define PAGE_DIRECTORY_PAGE_SIZE(x) ((x) << 7) // 4mib if 1, 4kib else
#define PAGE_DIRECTORY_TABLE_ADDRESS(x) ((x) << 12)

#define PAGE_TABLE_PRESENT(x) (x)
#define PAGE_TABLE_WRITABLE(x) ((x) << 1)
#define PAGE_TABLE_USER_ACCESSIBLE(x) ((x) << 2)
#define PAGE_TABLE_WRITE_THROUGH(x) ((x) << 3)
#define PAGE_TABLE_CACHE_DISABLED(x) ((x) << 4)
#define PAGE_TABLE_ACCESSED(x) ((x) << 5)
#define PAGE_TABLE_DIRTY(x) ((x) << 6)
#define PAGE_TABLE_GLOBAL(x) ((x) << 7)
#define PAGE_TABLE_PHYSICAL_ADDRESS(x) (((uint32_t) x) << 12)

typedef uint32_t page_dir_t;
typedef uint32_t page_table_t;

uint32_t k_base_physical_page_addr;
uint32_t k_end_physical_page_addr;

/**
 * Kernel pages
 * This basic setup limits the kernel memory to 4mib of memory
 */
page_dir_t kernel_page_dirs[PAGE_DIRECTORIES_AMOUNT]  __attribute__((aligned(4096)));
page_table_t kernel_page_tables[PAGE_DIRECTORIES_AMOUNT][PAGE_DIRECTORY_TABLES_AMOUNT]  __attribute__((aligned(4096)));

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
 * Map 0x00000000 - 0x3fffffff -> 0x00000000 - 0x3fffffff
 */
void init_kernel_paging() {
    uint16_t kernel_directory_start_i = 0x00000000 >> 22;
    uint16_t kernel_directory_end_i = 0x3fffffff >> 22;

    map_directories(
            kernel_directory_start_i, kernel_directory_end_i, 0,
            PAGE_DIRECTORY_PRESENT(1) | PAGE_DIRECTORY_WRITABLE(1),
            PAGE_TABLE_PRESENT(1) | PAGE_TABLE_WRITABLE(1)
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

    init_kernel_paging();
    enable_paging();
}

#endif //PAGING_H