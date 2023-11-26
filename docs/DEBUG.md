# ArtilleryOS Debugging with GDB

## Introduction

This guide provides instructions on using GDB (GNU Debugger) to debug ArtilleryOS, an operating system project. GDB is a powerful tool for debugging and analyzing the execution of programs.

## Prerequisites

Before you begin, ensure that you have the following installed on your system:

- **ArtilleryOS Source Code:** Obtain the source code for ArtilleryOS from the official repository.

- **QEMU:** Install QEMU on your system. This is the emulator that will be used for running ArtilleryOS during debugging.

- **GDB:** Install GDB on your system. You can typically install it using your system's package manager.

## Debugging Steps

1. **Clone ArtilleryOS Repository:**

```bash
git clone https://github.com/your-username/artillery-os.git
cd artillery-os
```

2. **Build ArtilleryOS:**

Build the ArtilleryOS kernel following the project's build instructions.

3. **Start QEMU with GDB Server:**

Start QEMU with the GDB server, enabling remote debugging:

```bash
qemu-system-x86_64 -cdrom ./artillery.iso -gdb stdio -S
```
This will start QEMU, and it will wait for a GDB connection.

4.  **Launch GDB:**

Open a new terminal window and navigate to the ArtilleryOS source directory. Launch GDB:

```bash
gdb
```

5. **Load Symbol Files:**

Load the symbol file for the kernel.elf at the correct address:

add-symbol-file ./kernel.elf 0xC0100000

6. **Set Disassembly Flavor:**

Set the disassembly flavor to Intel syntax for readability:

```bash
set disassembly-flavor intel
```

7. **Set Breakpoint:**

Set a breakpoint at a specific line in the source code (e.g., kernel.c:43):

```bash
break kernel.c:43
```

8. **Connect to QEMU:**

Connect GDB to the QEMU GDB server:

```bash
target remote | qemu-system-x86_64 -cdrom ./artillery.iso -gdb stdio -S
```

9. **Continue Execution:**

Continue the execution

```bash
continue
```

10. **View Assembly Code:**

Use the layout asm command to view the assembly code:

```bash
layout asm

```

11. **Exit GDB:**

To exit GDB and terminate the QEMU instance, use:

```bash
quit
```

