#include <stdint.h>

#define PAGE_DIRECTORIES_AMOUNT (1024)
#define PAGE_DIRECTORY_TABLES_AMOUNT (1024)
#define PAGE_SIZE (0x100)

class physical_page {
private:
    uint32_t page_start_addr;

    explicit physical_page(uint32_t page_start_addr): page_start_addr(page_start_addr) {

    }
public:
    static physical_page from(void *addr) {
        return physical_page::from((uint32_t) addr);
    }

    static physical_page from(uint32_t addr) {
        return physical_page(addr / PAGE_SIZE);
    }
};

class virtual_page {
private:
    uint32_t page_start_addr;

    explicit virtual_page(uint32_t page_start_addr): page_start_addr(page_start_addr) {

    }
public:
    static virtual_page from(void *addr) {
        return virtual_page::from((uint32_t) addr);
    }

    static virtual_page from(uint32_t addr) {
        return virtual_page(addr / PAGE_SIZE);
    }

    map_to() {

    }
};

class page_mapping {
    void map(void* virtual_page) {

    }
};

class page_manager {
public:
    void switch_mapping() {

    }
};

// add-symbol-file ~/Desktop/pyros-clean/cmake-build-debug/pyros.elf 0xc0000000

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