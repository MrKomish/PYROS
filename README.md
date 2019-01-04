# PYROS

A basic x86 operating system in development

Files:
- CMakeLists.txt - CMake build config
- Toolchain-i686-elf.cmake - Config cross compilation

/src

- init.asm - The first code to be executed
- main.c, main.h - Main init & OS logic.
- multiboot.asm - Multiboot config.
- linker.ld - Linker config.
- gdtlib.c, gdtlib.h - Global Descriptor Table generic library
- gdt.c, gdt.asm, gdt.h - Global Descriptor Table configuration and initialization specific for PYROS
- idtlib.c, idtlib.h - Interrupt Descriptor Table generic library
- idt.c, idt.asm, idt.h - Interrupt Descriptor Table configuration and initialization specific for PYROS
- timer.c, timer.h - System timer logic.
- sched.c, sched.h - Scheduler.

## Requirements

* CMake & Make
* Cross-Compiled i686-elf-gcc
* qemu-system-i386

Clion is Highly Recommended

## Usage

Building (Development Build):

```
$ ./build.sh
```

Running:

```
$ qemu-system-i386 -kernel cmake-build-debug/pyros.elf -monitor stdio
```

Debugging:

```
$ qemu-system-i386 -S -gdb tcp::1234 -kernel cmake-build-debug/pyros.elf -monitor stdio
```
And in gdb
```
file ./cmake-build-debug/pyros.elf
target remote localhost:1234
```