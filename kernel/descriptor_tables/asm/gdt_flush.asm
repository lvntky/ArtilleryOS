%define KERNEL_DATA_SEGMENT 0x10
%define CODE_DATA_SEGMENT 0x08

global _gdt_flush
extern _gp
_gdt_flush:
    lgdt [_gp]
    mov ax, KERNEL_DATA_SEGMENT
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp CODE_DATA_SEGMENT:flush2
flush2:
    ret