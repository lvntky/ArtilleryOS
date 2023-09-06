;--------------------------------;
;   Artillery OS                 ;
;   Kernel Entry point           ;
;   SEP. 20230 - Levent Kaya     ;
;--------------------------------;

[BITS 16]

CODE_SEG equ 0x08
DATA_SEG equ 0x10

load32:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x00200000
    mov esp, ebp

    ; Enable A20 line
    in al, 0x92,
    or al, 2
    out 0x92, al

    jmp $