cmake_minimum_required(VERSION 3.4)

if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "./Toolchain-i686-elf.cmake" CACHE PATH "toolchain file")
endif ()

# We have to set LANGUAGES to none so that we can set CMAKE_C_COMPILER
# before it checks the C compiler features. We can then use enable_language()
# to initialize all the C and ASM rules
project(pyros)

enable_language(ASM_NASM)

set (CMAKE_ASM_NASM_OBJECT_FORMAT elf)
set (CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> \
    <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_ASM_NASM_FLAGS "${ASM_NASM_FLAGS} -g -Fdwarf")
else()
    set(CMAKE_ASM_NASM_FLAGS "${ASM_NASM_FLAGS}")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -masm=intel")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -masm=intel")

file(GLOB SOURCE_FILES
        "src/*.h"
        "src/*.c"
        "src/*.asm"
        "src/interrupts/*.h"
        "src/interrupts/*.c"
        "src/interrupts/*.asm"
        "src/io/*.h"
        "src/io/*.c"
        "src/io*.asm"
        "src/memory/*.h"
        "src/memory/*.c"
        "src/memory/*.asm")

add_executable(pyros.elf ${SOURCE_FILES})

set_target_properties(pyros.elf PROPERTIES LINK_DEPENDS ../src/linker.ld)
set_target_properties(pyros.elf PROPERTIES LINK_FLAGS "-T ../src/linker.ld")
