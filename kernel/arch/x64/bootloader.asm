;------------------------------------------------;
; ArtilleryOS                                    ;
; 2023 - Levent Kaya                             ;
; Boot Loader                                    ;
;------------------------------------------------;

org 0x7C00
section .text
    ; stacl setup
    xor ax, ax
    mov ss, ax
    mov sp, 0x7C00

    ; Load the next sector (Artillery Os Kernel)
    mov ax, 0x0201  ; Number of sectors to read (1 sector)
    mov bx, 0x0002  ; Address to load the sector into (0x0002 = 512 bytes)
    mov dl, 0x80    ; Drive number (0x80 for the first hard drive)
    mov dh, 0       ; Head number
    mov ch, 0       ; Track number
    mov cl, 2       ; Sector number (the sector after the bootloader)
    mov ah, 0x02    ; BIOS read sector function
    int 0x13        ; Call BIOS interrupt to read the sector

    mov ax, 0x0002  ; Set the segment where the code was loaded
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ax, 0x0000  ; Set the instruction pointer to the start of the loaded code
    jmp 0x0000:0x0200  ; Jump to the loaded code

    times 510-($-$$) db 0  ; Pad the bootloader to 510 bytes
    dw 0xAA55             ; Boot signature (0xAA55)