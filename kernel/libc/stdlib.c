#include "include/stdlib.h"

static int rand_seed;


int abs(int x)
{
	if (x < 0) {
		return -x;
	}
	return x;
}


// simple xorshift implementation for pseudorandom number generation

void srand(int seed){
    rand_seed = seed; // should add ability to seed with time
}


int xorshift32(){
    rand_seed ^= (rand_seed << 13);
    rand_seed ^= (rand_seed >> 17);
    rand_seed ^= (rand_seed << 5);
    return rand_seed;
}


int rand(int min, int max){
    if(max <= min){
	return min;
    }
    return xorshift32() % (max-min+1) + min;
}
