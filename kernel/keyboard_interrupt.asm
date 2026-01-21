global keyboard_interrupt_handler
extern keyboard_handler

keyboard_interrupt_handler:
    pusha
    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    call keyboard_handler

    pop gs
    pop fs
    pop es
    pop ds
    popa

    iret