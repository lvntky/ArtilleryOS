#include "../include/kernel_heap.h"

static header_t base;
static header_t *freep = 0;

void kmalloc_init(uint32_t addr, size_t nbytes)
{
	header_t *p;
	size_t nunits;

	if (freep == 0) {
		base.s.next = freep = &base;
		base.s.size = 0;
	}

	nunits = (nbytes + sizeof(header_t) - 1) / sizeof(header_t) + 1;

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

void *kmalloc(size_t nbytes)
{
	header_t *p, *prevp;
	size_t nunits;

	if (nbytes == 0) {
		return 0;
	}

	//TODO: %u implementation needed
	nunits = (nbytes + sizeof(header_t) - 1) / sizeof(header_t) + 1;
	qemu_write_string("%s kmalloc() nbytes: %d, nunits %d\n",
			  INFORMATION_OUTPUT, nbytes, nunits);
	prevp = freep;

	for (p = prevp->s.next;; prevp = p, p = p->s.next) {
		if (p->s.size >= nunits) {
			/* the block is big enough */
			if (p->s.size == nunits) {
				/* exactly */
				prevp->s.next = p->s.next;
			} else {
				/* allocate at the tail end of the block and create a new
                 * header in front of allocated block */
				p->s.size -= nunits;
				p += p->s.size; /* make p point to new header */
				p->s.size = nunits;
			}
			freep = prevp;
			qemu_write_string("%s malloc: %x (header_t: %x)\n",
					  INFORMATION_OUTPUT, (uint32_t)(p + 1),
					  (uint32_t)p);
			return (void *)(p + 1);
		}
		if (p == freep) {
			qemu_write_string(
				"%s kmalloc() cannot allocate memory sizeof %d\n",
				NEGATIVE_OUTPUT, nbytes);
		}
	}
}

void kfree(void *ap)
{
	header_t *bp, *p;

	if (ap == 0)
		return;

	bp = (header_t *)ap - 1;
	for (p = freep; !(bp > p && bp < p->s.next); p = p->s.next) {
		if (p >= p->s.next && (bp > p || bp < p->s.next)) {
			break;
		}
	}

	if (bp + bp->s.size == p->s.next) {
		bp->s.size += p->s.next->s.size;
		bp->s.next = p->s.next->s.next;
	} else {
		bp->s.next = p->s.next;
	}

	if (p + p->s.size == bp) {
		p->s.size += bp->s.size;
		p->s.next = bp->s.next;
	} else {
		p->s.next = bp;
	}
	freep = p;
}