#include "include/stdlib.h"
#include "../include/stddef.h"

static short rand_seed;
char memory[MEMORY_SIZE];
Node *head;

int abs(int x)
{
	if (x < 0) {
		return -x;
	}
	return x;
}

// simple xorshift implementation for pseudorandom number generation

void srand(short seed)
{
	rand_seed = seed; // should add ability to seed with time
}

static short xorshift32()
{
	rand_seed ^= (rand_seed << 13);
	rand_seed ^= (rand_seed >> 17);
	rand_seed ^= (rand_seed << 5);
	return rand_seed;
}

int rand(int min, int max)
{
	if (max <= min) {
		return min;
	}
	return (int)(xorshift32()) % (max - min + 1) + min;
}