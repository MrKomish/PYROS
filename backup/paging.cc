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