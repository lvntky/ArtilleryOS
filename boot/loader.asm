;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                   ;
;   Artillery OS GRUB BootLoader    ;
;                                   ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

[BITS 32]
[global loader]
[extern kernel_main]

; Setting up multibootheaders for GRUB
MODULEALIGN equ 1<<0 ; align loaded modules on page boundary

MEMINFO equ 1<<1 ; provide memory map
FLAGS equ MODULEALIGN | MEMINFO
MAGIC equ 0x1BADB002

CHECKSUM equ -(MAGIC + FLAGS) ; checksum required

section .text

align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

loader:
    mov esp, stack+STACKSIZE ; set up the stack pointer
    push eax ; eax holds the MAGIC number
    push ebx ; ebx holds the Multiboot info

    call kernel_main

hang:
    jmp hang ; loop forever

; reserving initial stack size
STACKSIZE equ 0x4000 ; 16kB

align 4
stack:
    resb STACKSIZE ; reserve memory for stack on doubleworded memory
