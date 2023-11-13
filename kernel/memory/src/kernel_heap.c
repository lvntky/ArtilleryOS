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