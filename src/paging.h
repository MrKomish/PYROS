#include <stdint.h>

/**
 * https://wiki.osdev.org/Paging
 * http://www.renyujie.net/articles/article_ca_x86_5.php
 */

#define PAGE_DIRECTORY_PRESENT (x) (x)
#define PAGE_DIRECTORY_WRITABLE (x) ((x) << 1)
#define PAGE_DIRECTORY_USER_ACCESSIBLE (x) ((x) << 2)
#define PAGE_DIRECTORY_WRITE_THROUGH (x) ((x) << 3)
#define PAGE_DIRECTORY_CACHE_DISABLED (x) ((x) << 4)
#define PAGE_DIRECTORY_ACCESSED (x) ((x) << 5)
#define PAGE_DIRECTORY_SIZE (x) ((x) << 6) // 4mib if 1, 4kib else

#define PAGE_TABLE_PRESENT (x) (x)
#define PAGE_TABLE_WRITABLE (x) ((x) << 1)
#define PAGE_TABLE_USER_ACCESSIBLE (x) ((x) << 2)
#define PAGE_TABLE_WRITE_THROUGH (x) ((x) << 3)
#define PAGE_TABLE_CACHE_DISABLED (x) ((x) << 4)
#define PAGE_TABLE_ACCESSED (x) ((x) << 5)
#define PAGE_TABLE_DIRTY (x) ((x) << 6)
#define PAGE_TABLE_GLOBAL (x) ((x) << 7)

uint32_t page_directory[1024] __attribute__((aligned(4096)));

