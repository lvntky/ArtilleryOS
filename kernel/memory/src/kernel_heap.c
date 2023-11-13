#include "../include/kernel_heap.h"

// Define the base block for heap management
static header_t base;

// Pointer to the free list of blocks
static header_t *freep = 0;

// Initialize the kernel heap manager
void kmalloc_init(uint32_t addr, size_t nbytes)
{
	header_t *p;
	size_t nunits;

	// Check if the free list is empty
	if (freep == 0) {
		base.s.next = freep = &base;
		base.s.size = 0;
	}

	// Calculate the number of units needed for the given nbytes
	nunits = (nbytes + sizeof(header_t) - 1) / sizeof(header_t) + 1;

	// Initialize a header for the initial block and free it
	p = (header_t *)addr;
	p->s.size = nunits;
	kfree((void *)(p + 1));

	// TODO: %u implementation needed
	qemu_write_string("%s kmalloc initialized\n", POSITIVE_OUTPUT);
	qemu_write_string("%s p: %x, size: %d\n", INFORMATION_OUTPUT,
			  (uint32_t)p, p->s.size);
	qemu_write_string("%s base: %x, size: %d\n", INFORMATION_OUTPUT,
			  (uint32_t)&base, base.s.size);
}

// Allocate memory from the kernel heap
// Allocate memory from the kernel heap
void *kmalloc(size_t nbytes)
{
	header_t *p, *prevp;
	size_t nunits;

	// Check if nbytes is zero
	if (nbytes == 0) {
		return 0;
	}

	// Calculate the number of units needed for the given nbytes
	nunits = (nbytes + sizeof(header_t) - 1) / sizeof(header_t) + 1;
	qemu_write_string("%s kmalloc() nbytes: %d, nunits %d\n",
			  INFORMATION_OUTPUT, nbytes, nunits);
	prevp = freep;

	// Search for a free block that can accommodate the requested size
	for (p = prevp->s.next;; prevp = p, p = p->s.next) {
		if (p->s.size >= nunits) {
			// The block is big enough

			// If the block size is exactly the same as needed
			if (p->s.size == nunits) {
				prevp->s.next = p->s.next;
			} else {
				// Allocate at the tail end of the block and create a new header
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}

			// Update the free list pointer
			freep = prevp;

			// Print allocation details
			qemu_write_string("%s Allocation successful:\n",
					  POSITIVE_OUTPUT);
			qemu_write_string("%s   - Address: %x\n",
					  INFORMATION_OUTPUT,
					  (uint32_t)(p + 1));
			qemu_write_string("%s   - Header Address: %x\n",
					  INFORMATION_OUTPUT, (uint32_t)p);
			qemu_write_string("%s   - Allocated Size: %d units\n",
					  INFORMATION_OUTPUT, nunits);

			return (void *)(p + 1);
		}

		// Check if we have traversed the entire free list
		if (p == freep) {
			qemu_write_string(
				"%s kmalloc() cannot allocate memory sizeof %d\n",
				NEGATIVE_OUTPUT, nbytes);
			break;
		}
	}

	return NULL;
}

// Free a previously allocated block in the kernel heap
void kfree(void *ap)
{
	header_t *bp, *p;

	// Check if the pointer is null
	if (ap == 0)
		return;

	// Calculate the header pointer from the user pointer
	bp = (header_t *)ap - 1;

	// Search for the correct position in the free list to insert the block
	for (p = freep; !(bp > p && bp < p->s.next); p = p->s.next) {
		if (p >= p->s.next && (bp > p || bp < p->s.next)) {
			break;
		}
	}

	// Merge with the next block if contiguous
	if (bp + bp->s.size == p->s.next) {
		bp->s.size += p->s.next->s.size;
		bp->s.next = p->s.next->s.next;
	} else {
		bp->s.next = p->s.next;
	}

	// Merge with the previous block if contiguous
	if (p + p->s.size == bp) {
		p->s.size += bp->s.size;
		p->s.next = bp->s.next;
	} else {
		p->s.next = bp;
	}

	// Update the free list pointer
	freep = p;
}
