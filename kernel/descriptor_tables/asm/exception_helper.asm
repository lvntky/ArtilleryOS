global exception0
global exception1
global exception2
global exception3
global exception4
global exception5
global exception6
global exception7
global exception8
global exception9
global exception10
global exception11
global exception12
global exception13
global exception14
global exception15
global exception16
global exception17
global exception18
global exception19
global exception20
global exception21
global exception22
global exception23
global exception24
global exception25
global exception26
global exception27
global exception28
global exception29
global exception30
global exception31

;  0: Divide By Zero Exception
exception0:
    cli
    push byte 0
    push byte 0
    jmp isr_common_stub

;  1: Debug Exception
exception1:
    cli
    push byte 0
    push byte 1
    jmp isr_common_stub

;  2: Non Maskable Interrupt Exception
exception2:
    cli
    push byte 0
    push byte 2
    jmp isr_common_stub

;  3: Int 3 Exception
exception3:
    cli
    push byte 0
    push byte 3
    jmp isr_common_stub

;  4: INTO Exception
exception4:
    cli
    push byte 0
    push byte 4
    jmp isr_common_stub

;  5: Out of Bounds Exception
exception5:
    cli
    push byte 0
    push byte 5
    jmp isr_common_stub

;  6: Invalid Opcode Exception
exception6:
    cli
    push byte 0
    push byte 6
    jmp isr_common_stub

;  7: Coprocessor Not Available Exception
exception7:
    cli
    push byte 0
    push byte 7
    jmp isr_common_stub

;  8: Double Fault Exception (With Error Code!)
exception8:
    cli
    push byte 8
    jmp isr_common_stub

;  9: Coprocessor Segment Overrun Exception
exception9:
    cli
    push byte 0
    push byte 9
    jmp isr_common_stub

; 10: Bad TSS Exception (With Error Code!)
exception10:
    cli
    push byte 10
    jmp isr_common_stub

; 11: Segment Not Present Exception (With Error Code!)
exception11:
    cli
    push byte 11
    jmp isr_common_stub

; 12: Stack Fault Exception (With Error Code!)
exception12:
    cli
    push byte 12
    jmp isr_common_stub

; 13: General Protection Fault Exception (With Error Code!)
exception13:
    cli
    push byte 13
    jmp isr_common_stub

; 14: Page Fault Exception (With Error Code!)
exception14:
    cli
    push byte 14
    jmp isr_common_stub

; 15: Reserved Exception
exception15:
    cli
    push byte 0
    push byte 15
    jmp isr_common_stub

; 16: Floating Point Exception
exception16:
    cli
    push byte 0
    push byte 16
    jmp isr_common_stub

; 17: Alignment Check Exception
exception17:
    cli
    push byte 0
    push byte 17
    jmp isr_common_stub

; 18: Machine Check Exception
exception18:
    cli
    push byte 0
    push byte 18
    jmp isr_common_stub

; 19: Reserved
exception19:
    cli
    push byte 0
    push byte 19
    jmp isr_common_stub

; 20: Reserved
exception20:
    cli
    push byte 0
    push byte 20
    jmp isr_common_stub

; 21: Reserved
exception21:
    cli
    push byte 0
    push byte 21
    jmp isr_common_stub

; 22: Reserved
exception22:
    cli
    push byte 0
    push byte 22
    jmp isr_common_stub

; 23: Reserved
exception23:
    cli
    push byte 0
    push byte 23
    jmp isr_common_stub

; 24: Reserved
exception24:
    cli
    push byte 0
    push byte 24
    jmp isr_common_stub

; 25: Reserved
exception25:
    cli
    push byte 0
    push byte 25
    jmp isr_common_stub

; 26: Reserved
exception26:
    cli
    push byte 0
    push byte 26
    jmp isr_common_stub

; 27: Reserved
exception27:
    cli
    push byte 0
    push byte 27
    jmp isr_common_stub

; 28: Reserved
exception28:
    cli
    push byte 0
    push byte 28
    jmp isr_common_stub

; 29: Reserved
exception29:
    cli
    push byte 0
    push byte 29
    jmp isr_common_stub

; 30: Reserved
exception30:
    cli
    push byte 0
    push byte 30
    jmp isr_common_stub

; 31: Reserved
exception31:
    cli
    push byte 0
    push byte 31
    jmp isr_common_stub


; We call a C function in here. We need to let the assembler know
; that '_fault_handler' exists in another file
extern exception_fault_handler

; This is our common ISR stub. It saves the processor state, sets
; up for kernel mode segments, calls the C-level fault handler,
; and finally restores the stack frame.

isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, exception_fault_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret