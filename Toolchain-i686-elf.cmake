# this one is important
SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_PROCESSOR i686)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
SET(CMAKE_C_COMPILER   clang)
SET(CMAKE_CXX_COMPILER clang++)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# TODO remove -mgeneral-regs-only in the future
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --target=i686-pc-none-elf -march=i686 -nostdlib -ffreestanding")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --target=i686-pc-none-elf -march=i686 -nostdlib -ffreestanding")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib" )

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
