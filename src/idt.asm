section .text
align 4

extern kprint

global int_ignore

; default interrupt handler
int_ignore:
    push ebp
    mov ebp, esp

    push int_ignore_msg
    call kprint

    mov esp, ebp
    pop ebp

	iret

section .data

int_ignore_msg:
    db `DEFAULT INTTERUPT HANDLER HAS BEEN ISSUED!\n`