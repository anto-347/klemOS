BOOT_DRIVE: db 0
CODE_SEG equ 0x08
DATA_SEG equ 0x10

gdt_start:
    dw 0x0
    dw 0x0
    db 0x0
    db 0x0
    db 0x0
    db 0x0

gdt_code:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0

gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start


mov [BOOT_DRIVE], dl
mov bx, 0x1000
mov dh, 0x00
mov dl, [BOOT_DRIVE]
mov ah, 0x02
mov al, 16
mov cl, 0x02
mov ch, 0x00
int 0x13

jc disk_error

cli
lgdt [gdt_descriptor]
mov eax, cr0
or eax, 0x1
mov cr0, eax
jmp CODE_SEG:init_pm

[bits 32]
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    mov ebp, 0x90000
    mov esp, ebp

    call CODE_SEG:0x1000

hang:
    jmp hang

times 510-($-$$) db 0

dw 0xAA55