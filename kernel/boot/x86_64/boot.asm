;--------------------------------;
;   Artillery OS                 ;
;   Bootloader                   ;
;   SEP. 2023 - Levent Kaya      ;
;--------------------------------;

ORG 0X7C00
[BITS 16]

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

jmp short start
nop


start:
    jmp 0:step2

step2:
    cli 
    mov ax, 0x00
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00
    sti 

.load_protected:
    cli
    lgdt[gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:load32

; GDT
gdt_start:
gdt_null:
    dd 0x0
    dd 0x0

; offset 0x8
gdt_code:     
    dw 0xffff 
    dw 0      
    db 0      
    db 0x9a   
    db 11001111b 
    db 0        

gdt_data:      
    dw 0xffff 
    dw 0      
    db 0      
    db 0x92   
    db 11001111b 
    db 0   
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start-1
    dd gdt_start

 [BITS 32]
 load32:
    mov eax, 1
    mov ecx, 100
    mov edi, 0x0100000
    call ata_lba_read
    jmp CODE_SEG:0x0100000

ata_lba_read:
    mov ebx, eax, 
    
    shr eax, 24
    or eax, 0xE0 
    mov dx, 0x1F6
    out dx, al
    

    
    mov eax, ecx
    mov dx, 0x1F2
    out dx, al
    

    
    mov eax, ebx 
    mov dx, 0x1F3
    out dx, al
    

    
    mov dx, 0x1F4
    mov eax, ebx 
    shr eax, 8
    out dx, al
    

    
    mov dx, 0x1F5
    mov eax, ebx 
    shr eax, 16
    out dx, al
    

    mov dx, 0x1f7
    mov al, 0x20
    out dx, al

    
.next_sector:
    push ecx


.try_again:
    mov dx, 0x1f7
    in al, dx
    test al, 8
    jz .try_again


    mov ecx, 256
    mov dx, 0x1F0
    rep insw
    pop ecx
    loop .next_sector
    ls
    ret

times 510-($ - $$) db 0
dw 0xAA55