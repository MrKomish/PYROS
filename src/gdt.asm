section .text
align 4

extern GDT

global gdt_flush

gdt_flush:

    ; mov dword [0xb8000], 0x2f4b2f4f
    ; hlt

    lgdt [GDT]

	gdt_flush_code:
		jmp 0x08: gdt_flush_data

	gdt_flush_data:
		mov ax, 0x10 ;; data segment

		mov ds, ax   ;; update all data segments
		mov ss, ax
		mov ds, ax
		mov es, ax
		mov fs, ax
		mov gs, ax

	ret