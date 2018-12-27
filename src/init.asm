global kenter

extern gdt_init
extern kmain

KERNEL_STACK_SIZE equ 4096

section .text
bits 32
align 4

	kenter:

		mov esp, kstack_top

        call gdt_init

		push edx
		push ebx
		call kmain

	hang:

        cli ; Disable CPU interrupts
        hlt ; Halt the CPU
		jmp hang

section .bss
align 4
	kstack_bottom:
		resb KERNEL_STACK_SIZE
	kstack_top:

