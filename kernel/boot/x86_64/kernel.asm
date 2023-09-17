[BITS 32]

global _start
extern kernel_main

CODE_SEG equ 0x08
DATA_SEG equ 0x10

_start:
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov ebp, 0x00200000
    mov esp, ebp

    ; enable A20
    in al, 0x92
    or al, 2
    out 0x92, al

    ; Remap the master PIC
    mov al, 00010001b  ; Move the binary value 00010001 into the AL register
    out 0x20, al       ; Send the value in AL to port 0x20 (Master PIC Command)

    mov al, 0x20       ; Load the value 0x20 into the AL register
    out 0x21, al       ; Send the value in AL to port 0x21 (Master PIC Data)

    mov al, 00000001b  ; Move the binary value 00000001 into the AL register
    out 0x21, al       ; Send the value in AL to port 0x21 (Master PIC Data)
    ; End remap of the master PIC
    
    sti ; enable the interrupts

    call kernel_main

    jmp $


times 512 - ($ - $$) db 0
