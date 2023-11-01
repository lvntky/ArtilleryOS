#ifndef _ISR_H_
#define _ISR_H_

#include "../../include/registert.h"
#include "../../include/qemu_debug.h"
#include "../../include/panic.h"
#include "../../libc/include/string.h"
#include "../../driver/include/pic.h"

// BASE INTERRUPTS
extern void exception0();
extern void exception1();
extern void exception2();
extern void exception3();
extern void exception4();
extern void exception5();
extern void exception6();
extern void exception7();
extern void exception8();
extern void exception9();
extern void exception10();
extern void exception11();
extern void exception12();
extern void exception13();
extern void exception14();
extern void exception15();
extern void exception16();
extern void exception17();
extern void exception18();
extern void exception19();
extern void exception20();
extern void exception21();
extern void exception22();
extern void exception23();
extern void exception24();
extern void exception25();
extern void exception26();
extern void exception27();
extern void exception28();
extern void exception29();
extern void exception30();
extern void exception31();

// BASE INTERRUPTS
extern void interrupt0();
extern void interrupt1();
extern void interrupt2();
extern void interrupt3();
extern void interrupt4();
extern void interrupt5();
extern void interrupt6();
extern void interrupt7();
extern void interrupt8();
extern void interrupt9();
extern void interrupt10();
extern void interrupt11();
extern void interrupt12();
extern void interrupt13();
extern void interrupt14();
extern void interrupt15();

// kernel_level_exceptions
void exception_fault_handler(register_t *);

//INTERRUPT METHODS
void install_interrupt_handler(int, void (*handler)(register_t *));
void interrupt_handler(register_t *);

#endif