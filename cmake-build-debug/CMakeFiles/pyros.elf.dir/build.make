# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/komish/Software/cmake-3.12.2-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/komish/Software/cmake-3.12.2-Linux-x86_64/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/komish/Desktop/pyros-clean

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/komish/Desktop/pyros-clean/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/pyros.elf.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pyros.elf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pyros.elf.dir/flags.make

CMakeFiles/pyros.elf.dir/src/gdt.asm.obj: CMakeFiles/pyros.elf.dir/flags.make
CMakeFiles/pyros.elf.dir/src/gdt.asm.obj: ../src/gdt.asm
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/komish/Desktop/pyros-clean/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building ASM_NASM object CMakeFiles/pyros.elf.dir/src/gdt.asm.obj"
	/usr/bin/nasm $(ASM_NASM_INCLUDES)     $(ASM_NASM_FLAGS) -f elf -o CMakeFiles/pyros.elf.dir/src/gdt.asm.obj /home/komish/Desktop/pyros-clean/src/gdt.asm

CMakeFiles/pyros.elf.dir/src/gdt.c.obj: CMakeFiles/pyros.elf.dir/flags.make
CMakeFiles/pyros.elf.dir/src/gdt.c.obj: ../src/gdt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/komish/Desktop/pyros-clean/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/pyros.elf.dir/src/gdt.c.obj"
	/opt/cross-compiler/i686-elf/out/path/bin/i686-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pyros.elf.dir/src/gdt.c.obj   -c /home/komish/Desktop/pyros-clean/src/gdt.c

CMakeFiles/pyros.elf.dir/src/gdt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pyros.elf.dir/src/gdt.c.i"
	/opt/cross-compiler/i686-elf/out/path/bin/i686-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/komish/Desktop/pyros-clean/src/gdt.c > CMakeFiles/pyros.elf.dir/src/gdt.c.i

CMakeFiles/pyros.elf.dir/src/gdt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pyros.elf.dir/src/gdt.c.s"
	/opt/cross-compiler/i686-elf/out/path/bin/i686-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/komish/Desktop/pyros-clean/src/gdt.c -o CMakeFiles/pyros.elf.dir/src/gdt.c.s

CMakeFiles/pyros.elf.dir/src/gdtlib.c.obj: CMakeFiles/pyros.elf.dir/flags.make
CMakeFiles/pyros.elf.dir/src/gdtlib.c.obj: ../src/gdtlib.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/komish/Desktop/pyros-clean/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/pyros.elf.dir/src/gdtlib.c.obj"
	/opt/cross-compiler/i686-elf/out/path/bin/i686-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pyros.elf.dir/src/gdtlib.c.obj   -c /home/komish/Desktop/pyros-clean/src/gdtlib.c

CMakeFiles/pyros.elf.dir/src/gdtlib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pyros.elf.dir/src/gdtlib.c.i"
	/opt/cross-compiler/i686-elf/out/path/bin/i686-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/komish/Desktop/pyros-clean/src/gdtlib.c > CMakeFiles/pyros.elf.dir/src/gdtlib.c.i

CMakeFiles/pyros.elf.dir/src/gdtlib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pyros.elf.dir/src/gdtlib.c.s"
	/opt/cross-compiler/i686-elf/out/path/bin/i686-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/komish/Desktop/pyros-clean/src/gdtlib.c -o CMakeFiles/pyros.elf.dir/src/gdtlib.c.s

CMakeFiles/pyros.elf.dir/src/init.asm.obj: CMakeFiles/pyros.elf.dir/flags.make
CMakeFiles/pyros.elf.dir/src/init.asm.obj: ../src/init.asm
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/komish/Desktop/pyros-clean/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building ASM_NASM object CMakeFiles/pyros.elf.dir/src/init.asm.obj"
	/usr/bin/nasm $(ASM_NASM_INCLUDES)     $(ASM_NASM_FLAGS) -f elf -o CMakeFiles/pyros.elf.dir/src/init.asm.obj /home/komish/Desktop/pyros-clean/src/init.asm

CMakeFiles/pyros.elf.dir/src/main.c.obj: CMakeFiles/pyros.elf.dir/flags.make
CMakeFiles/pyros.elf.dir/src/main.c.obj: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/komish/Desktop/pyros-clean/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/pyros.elf.dir/src/main.c.obj"
	/opt/cross-compiler/i686-elf/out/path/bin/i686-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pyros.elf.dir/src/main.c.obj   -c /home/komish/Desktop/pyros-clean/src/main.c

CMakeFiles/pyros.elf.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pyros.elf.dir/src/main.c.i"
	/opt/cross-compiler/i686-elf/out/path/bin/i686-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/komish/Desktop/pyros-clean/src/main.c > CMakeFiles/pyros.elf.dir/src/main.c.i

CMakeFiles/pyros.elf.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pyros.elf.dir/src/main.c.s"
	/opt/cross-compiler/i686-elf/out/path/bin/i686-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/komish/Desktop/pyros-clean/src/main.c -o CMakeFiles/pyros.elf.dir/src/main.c.s

CMakeFiles/pyros.elf.dir/src/multiboot.asm.obj: CMakeFiles/pyros.elf.dir/flags.make
CMakeFiles/pyros.elf.dir/src/multiboot.asm.obj: ../src/multiboot.asm
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/komish/Desktop/pyros-clean/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building ASM_NASM object CMakeFiles/pyros.elf.dir/src/multiboot.asm.obj"
	/usr/bin/nasm $(ASM_NASM_INCLUDES)     $(ASM_NASM_FLAGS) -f elf -o CMakeFiles/pyros.elf.dir/src/multiboot.asm.obj /home/komish/Desktop/pyros-clean/src/multiboot.asm

# Object files for target pyros.elf
pyros_elf_OBJECTS = \
"CMakeFiles/pyros.elf.dir/src/gdt.asm.obj" \
"CMakeFiles/pyros.elf.dir/src/gdt.c.obj" \
"CMakeFiles/pyros.elf.dir/src/gdtlib.c.obj" \
"CMakeFiles/pyros.elf.dir/src/init.asm.obj" \
"CMakeFiles/pyros.elf.dir/src/main.c.obj" \
"CMakeFiles/pyros.elf.dir/src/multiboot.asm.obj"

# External object files for target pyros.elf
pyros_elf_EXTERNAL_OBJECTS =

pyros.elf: CMakeFiles/pyros.elf.dir/src/gdt.asm.obj
pyros.elf: CMakeFiles/pyros.elf.dir/src/gdt.c.obj
pyros.elf: CMakeFiles/pyros.elf.dir/src/gdtlib.c.obj
pyros.elf: CMakeFiles/pyros.elf.dir/src/init.asm.obj
pyros.elf: CMakeFiles/pyros.elf.dir/src/main.c.obj
pyros.elf: CMakeFiles/pyros.elf.dir/src/multiboot.asm.obj
pyros.elf: CMakeFiles/pyros.elf.dir/build.make
pyros.elf: ../src/linker.ld
pyros.elf: CMakeFiles/pyros.elf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/komish/Desktop/pyros-clean/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable pyros.elf"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pyros.elf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pyros.elf.dir/build: pyros.elf

.PHONY : CMakeFiles/pyros.elf.dir/build

CMakeFiles/pyros.elf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pyros.elf.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pyros.elf.dir/clean

CMakeFiles/pyros.elf.dir/depend:
	cd /home/komish/Desktop/pyros-clean/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/komish/Desktop/pyros-clean /home/komish/Desktop/pyros-clean /home/komish/Desktop/pyros-clean/cmake-build-debug /home/komish/Desktop/pyros-clean/cmake-build-debug /home/komish/Desktop/pyros-clean/cmake-build-debug/CMakeFiles/pyros.elf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pyros.elf.dir/depend

