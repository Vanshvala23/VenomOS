[BITS 16]
[ORG 0x7C00]

start:
    mov ah, 0x0E      ; BIOS teletype output
    mov si, msg

print:
    lodsb             ; Load byte from SI into AL
    cmp al, 0
    je loading
    int 0x10
    jmp print

loading:
    mov si, loading_msg
    call print_str

    ; Simple loading animation
    mov cx, 10
loading_loop:
    mov al, '.'
    int 0x10
    call delay
    loop loading_loop

    ; Jump to kernel at 0x1000:0000
    jmp 0x1000:0x0000

print_str:
    lodsb
    cmp al, 0
    je done
    int 0x10
    jmp print_str
done:
    ret

delay:
    mov cx, 0xFFFF
delay_loop:
    loop delay_loop
    ret

msg db 'Welcome to SimpleOS! Loading...', 0
loading_msg db 'Loading Kernel', 0

times 510 - ($ - $$) db 0
dw 0xAA55
