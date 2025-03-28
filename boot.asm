[bits 16]                 ; 16-bit Real Mode
[org 0x7c00]              ; BIOS loads bootloader to 0x7C00

start:
    mov ah, 0x0e          ; BIOS teletype function
    mov al, 'S'           ; Print 'S'
    int 0x10
    mov al, 'O'           ; Print 'O'
    int 0x10
    mov al, 'S'           ; Print 'S'
    int 0x10

    ; Switch to 32-bit mode
    cli
    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp 0x08:start32

[bits 32]
start32:
    mov eax, 0x10
    mov ds, eax
    mov es, eax
    mov fs, eax
    mov gs, eax
    mov ss, eax
    call kernel_main

hang:
    hlt
    jmp hang

gdt_start:
    dq 0
    ; Code segment descriptor
    dw 0xffff, 0x0000, 0x9a00, 0x00cf
    ; Data segment descriptor
    dw 0xffff, 0x0000, 0x9200, 0x00cf
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

times 510-($-$$) db 0
dw 0xaa55
