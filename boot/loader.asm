[BITS 32]
global start
start:
    mov esp, _sys_stack
    mov ebx, mboot
    push ebx
    jmp stublet

ALIGN 4  ; Ensure proper alignment for the Multiboot header

global mboot
extern code
extern bss
extern end

mboot:
    align 4
    MULTIBOOT_MAGIC     equ 0x1BADB002
    MULTIBOOT_FLAGS     equ 0x03
    MULTIBOOT_CHECKSUM  equ -MULTIBOOT_MAGIC-MULTIBOOT_FLAGS
    
    dd MULTIBOOT_MAGIC  
    dd MULTIBOOT_FLAGS
    dd MULTIBOOT_CHECKSUM



extern kernel_main
stublet:
    call kernel_main
    jmp $

SECTION .bss
    resb 8192               
_sys_stack: