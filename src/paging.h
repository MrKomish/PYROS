#pragma once

#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>
#include "mem.h"
#include "control.h"

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

/*typedef struct {
    uint8_t present : 1;
    uint8_t writable : 1;
    uint8_t user_accessible : 1;
    uint8_t write_through : 1;
    uint8_t cache_disabled : 1;
    uint8_t accessed : 1;
    uint8_t zero : 1;
    uint8_t page_size : 1;
    uint8_t ignored : 1;
    uint8_t available : 3;
    uint32_t tables_address : 20;
} page_dir_t;*/

// page_dir_t page_dirs[1024] __attribute__((aligned(4096)));

uint32_t k_base_physical_page_addr;
uint32_t k_end_physical_page_addr;

/**
 * Kernel pages
 * This basic setup limits the kernel memory to 4mib of memory
 */
page_dir_t kernel_page_dirs[PAGE_DIRECTORIES_AMOUNT]  __attribute__((aligned(4096)));
page_table_t kernel_page_tables[PAGE_DIRECTORIES_AMOUNT][PAGE_DIRECTORY_TABLES_AMOUNT]  __attribute__((aligned(4096)));

void init_kernel_paging() {
    k_base_physical_page_addr = (((uint32_t) kernel_base_addr) / PAGE_SIZE) * PAGE_SIZE;
    k_end_physical_page_addr = (((uint32_t) kernel_end_addr) / PAGE_SIZE) * PAGE_SIZE;

    uint16_t kernel_directory_start_i = 0xc0000000 >> 22;
    uint16_t kernel_directory_end_i = 0xffffffff >> 22;

    for (uint16_t dir_i = kernel_directory_start_i; dir_i < kernel_directory_end_i; dir_i++) {
        page_dir_t* dir = &kernel_page_dirs[dir_i];

        *dir = PAGE_DIRECTORY_PRESENT(1) | PAGE_DIRECTORY_WRITABLE(1) | PAGE_DIRECTORY_USER_ACCESSIBLE(0)
                    | PAGE_DIRECTORY_WRITE_THROUGH(0) | PAGE_DIRECTORY_CACHE_DISABLED(0) |
                    PAGE_DIRECTORY_ACCESSED(0) | PAGE_DIRECTORY_PAGE_SIZE(0)
                    | ((uint32_t) &kernel_page_tables[dir_i]);

        for (uint16_t page_i = 0; page_i < PAGE_DIRECTORY_TABLES_AMOUNT; page_i++) {
            page_table_t* table = &kernel_page_tables[dir_i][page_i];

            *table = PAGE_TABLE_PRESENT(1) | PAGE_TABLE_WRITABLE(1) | PAGE_TABLE_USER_ACCESSIBLE(0)
                    | PAGE_TABLE_WRITE_THROUGH(0) | PAGE_TABLE_CACHE_DISABLED(0) | PAGE_TABLE_ACCESSED(0) | PAGE_TABLE_DIRTY(0) | PAGE_TABLE_GLOBAL(0)
                    | PAGE_TABLE_PHYSICAL_ADDRESS((dir_i - kernel_directory_start_i) * PAGE_DIRECTORY_TABLES_AMOUNT + page_i);
        }
    }
}

void enable_paging() {
    set_page_directory((const uint32_t) kernel_page_dirs);
    set_cr0(get_cr0() | CR0_PAGING_ENABLE);
}

void kinit_paging() {
    init_kernel_paging();
    enable_paging();

    /*uint32_t k_base_physical_page_addr = (((uint32_t) kernel_base_addr) / PAGE_SIZE) * PAGE_SIZE;
    uint32_t k_end_physical_page_addr = (((uint32_t) kernel_end_addr) / PAGE_SIZE) * PAGE_SIZE;

    k_end_physical_page_addr += PAGE_SIZE;

    k_end_physical_page_addr[0] =


    uint32_t k_page_tables_amount = k_base_physical_page_i - k_end_physical_page_i + 1;
    uint32_t k_page_directories_amount = k_page_tables_amount / PAGE_DIRECTORY_TABLES_AMOUNT;

    page_table_t* page_entries_physical_page = (page_table_t *) (kernel_end_physical_page + 0x1000);

    uint16_t dir_i = 0;
    uint16_t table_i = 0;

    for (uint32_t p_addr = kernel_base_physical_page; p_addr <= kernel_end_physical_page; p_addr += 0x1000) {

        page_table_t* page_entry = &page_entries_physical_page[dir_i * 0x400 + table_i];

        *page_entry = PAGE_TABLE_PRESENT(1) | PAGE_TABLE_WRITABLE(1) | PAGE_TABLE_USER_ACCESSIBLE(0)
                | PAGE_TABLE_WRITE_THROUGH(0) | PAGE_TABLE_CACHE_DISABLED(0) | PAGE_TABLE_ACCESSED(0) | PAGE_TABLE_DIRTY(0) | PAGE_TABLE_GLOBAL(0)
                | p_addr;

        table_i++;

        if (table_i == PAGE_DIRECTORY_TABLES_AMOUNT) {
            page_dir_t *page_dir = &page_dirs[dir_i];
            *page_dir = PAGE_DIRECTORY_PRESENT(1) | PAGE_DIRECTORY_WRITABLE(1) | PAGE_DIRECTORY_USER_ACCESSIBLE(0)
                        | PAGE_DIRECTORY_WRITE_THROUGH(0) | PAGE_DIRECTORY_CACHE_DISABLED(0) |
                        PAGE_DIRECTORY_ACCESSED(0) | PAGE_DIRECTORY_PAGE_SIZE(0) | PAGE_DIRECTORY_TABLE_ADDRESS(0)
                        | p_addr;

            table_i = 0;
            dir_i++;
        }

    }

    for (; table_i < PAGE_DIRECTORY_TABLES_AMOUNT; table_i++) {
        // p_addr += 0x1000;
    }

    for (int i = 0; i < PAGE_DIRECTORIES_AMOUNT; i++) {

    }*/
}

#endif //PAGING_H