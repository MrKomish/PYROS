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

uint32_t unused_page_addr;

/**
 * Kernel pages
 * This basic setup limits the kernel memory to 4mib of memory
 */
page_dir_t kernel_page_dirs[PAGE_DIRECTORIES_AMOUNT]  __attribute__((aligned(4096)));
page_table_t kernel_page_tables[PAGE_DIRECTORIES_AMOUNT][PAGE_DIRECTORY_TABLES_AMOUNT]  __attribute__((aligned(4096)));

void map_tables(uint16_t dir_i, uint16_t table_start_i, uint16_t table_end_i, uint32_t base_phys_page_addr,
                uint32_t table_flags);

void map_directories(uint16_t dir_start_i, uint16_t dir_end_i, uint16_t base_phys_dir_i, uint32_t dir_flags,
                     uint32_t table_flags);

void init_kernel_paging();
void enable_paging();
void kinit_paging();

#endif //PAGING_H