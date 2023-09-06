;--------------------------------;
;   Artillery OS                 ;
;   Bootloader                   ;
;   SEP. 2023 - Levent Kaya      ;
;--------------------------------;

ORG 0X7C00
[BITS 16]

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

_start:
    jmp short start
    nop

    times 33 db 0

start:
    jmp 0:step2

step2:
    cli ; clear interrupts
    mov ax, 0x00
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti ; enable interrupts

.load_protected:
    cli
    lgdt[gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    ;jmp CODE_SEG:load32
    jmp $

;GDT
gdt_start:
gdt_null:
    dd 0x00
    dd 0x00

; offset 0x8
gdt_code:
    dw 0xffff
    dw 0
    db 0
    db 0x9A
    db 11001111b
    db 0

gdt_data:
    dw 0xffff
    dw 0
    db 0
    db 0x9A
    db 11001111b
    db 0
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start-1
    dd gdt_start

times 510 -($ - $$) db 0
dw 0xAA55