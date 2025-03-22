[BITS 16]      ; 16-bit Real Mode
[ORG 0x7C00]   ; Bootloader loads at memory address 0x7C00

mov ah, 0x0E   ; BIOS teletype mode
mov al, 'B'    ; Print 'B'
int 0x10       ; Call BIOS interrupt

cli            ; Disable interrupts
lgdt [gdt_descriptor]  ; Load the GDT (for Protected Mode)
mov eax, cr0   
or eax, 1      ; Set the Protected Mode bit (PE)
mov cr0, eax   
jmp CODE_SEG:init_protected_mode  ; Far jump to new segment

[BITS 32]      ; Now in 32-bit Protected Mode
init_protected_mode:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov esp, 0x90000  ; Set stack pointer

    call kernel_main  ; Call our kernel (written in C)

    hlt              ; Halt if kernel returns

gdt_start:
    dq 0             ; Null Descriptor
gdt_code:
    dw 0xFFFF, 0, 0x9A, 0xCF  ; Code Segment
gdt_data:
    dw 0xFFFF, 0, 0x92, 0xCF  ; Data Segment
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; Size
    dd gdt_start                ; Address

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

times 510-($-$$) db 0  ; Pad boot sector to 512 bytes
dw 0xAA55  ; Boot signature
