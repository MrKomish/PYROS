file ./cmake-build-debug/pyros.elf

target remote | /usr/bin/qemu-system-i386 -S -gdb stdio -kernel cmake-build-debug/pyros.elf -monitor stdio