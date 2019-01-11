section .text
align 4

extern kprint
extern pic_send_eoi

global int_ignore
global int_time_tick

; default interrupt handler
int_ignore:
    push ebp
    mov ebp, esp

    sub esp, 4

    ; debugging only
    push int_ignore_msg
    call kprint

    leave
	iret

section .data

int_ignore_msg:
    db `DEFAULT INTTERUPT HANDLER HAS BEEN ISSUED!\n`