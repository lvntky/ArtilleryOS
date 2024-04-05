#include "include/stdlib.h"
static uint32_t rand_seed;

int abs(int x)
{
	if (x < 0) {
		return -x;
	}
	return x;
}

// simple xorshift implementation for pseudorandom number generation

void srand(uint32_t seed)
{
	rand_seed = seed; // should add ability to seed with time
}

static uint32_t xorshift32()
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

void *malloc(unsigned long long size)
{
	if (size == 0)
		return NULL;

	// Align size to the size of a Node
	unsigned long long aligned_size =
		(size + sizeof(Node) - 1) / sizeof(Node) * sizeof(Node);

	Node *current = head;
	Node *previous = NULL;

	while (current != NULL) {
		if (current->size >= aligned_size) {
			// Found a block big enough
			if (current->size > aligned_size + sizeof(Node)) {
				// Split the block
				Node *new_node =
					(Node *)((char *)current +
						 aligned_size + sizeof(Node));
				new_node->size = current->size - aligned_size -
						 sizeof(Node);
				new_node->next = current->next;
				current->next = new_node;
			}
			if (previous != NULL) {
				previous->next = current->next;
			} else {
				head = current->next;
			}
			return (char *)current + sizeof(Node);
		}
		previous = current;
		current = current->next;
	}

	// No suitable block found, allocate new memory
	Node *new_node = (Node *)memory;
	if (MEMORY_SIZE < aligned_size + sizeof(Node)) {
		// Memory is insufficient
		return NULL;
	}
	new_node->size = MEMORY_SIZE - sizeof(Node);
	new_node->next = NULL;
	if (MEMORY_SIZE > aligned_size + sizeof(Node)) {
		// Split the block
		Node *remaining_memory = (Node *)((char *)new_node +
						  aligned_size + sizeof(Node));
		remaining_memory->size =
			MEMORY_SIZE - aligned_size - sizeof(Node);
		remaining_memory->next = NULL;
		new_node->next = remaining_memory;
	}
	head = new_node;
	return (char *)new_node + sizeof(Node);
}

void *calloc(unsigned long long num_elements, unsigned long long element_size) {
    // Calculate total memory required
    unsigned long long total_size = num_elements * element_size;

    // Allocate memory using malloc
    void* ptr = malloc(total_size);

    // Check if memory allocation was successful
    if (ptr != NULL) {
        // Set all allocated memory to zero
        for (unsigned long long i = 0; i < total_size; ++i) {
            *((char*)ptr + i) = 0;
        }
    }

    return ptr;
}

void *realloc(void *ptr, unsigned long long new_size)
{
    // If ptr is NULL, realloc behaves like malloc
    if (ptr == NULL) {
        return malloc(new_size);
    }

    // If new_size is 0 and ptr is not NULL, realloc behaves like free
    if (new_size == 0) {
        free(ptr);
        return NULL;
    }

    // Allocate memory for the new size
    void* new_ptr = malloc(new_size);
    if (new_ptr == NULL) {
        return NULL; // Memory allocation failed
    }

    // Copy contents from old memory block to new memory block
    // Copy up to the minimum of the old and new sizes
    size_t old_size = sizeof(ptr);
    if (new_size < old_size) {
        old_size = new_size;
    }

    for (size_t i = 0; i < old_size; ++i) {
        *((char*)new_ptr + i) = *((char*)ptr + i);
    }

    // Free the old memory block
    free(ptr);

    return new_ptr;
}


void free(void *ptr)
{
	if (ptr == NULL)
		return;

	Node *freed_block = (Node *)((char *)ptr - sizeof(Node));
	Node *current = head;

	// Find the correct position to insert the freed block
	while (current != NULL) {
		if ((char *)current + current->size + sizeof(Node) ==
		    (char *)freed_block) {
			// Merge the freed block with the next block
			current->size += sizeof(Node) + freed_block->size;
			freed_block = current;
			break;
		}
		if ((char *)freed_block + freed_block->size + sizeof(Node) ==
		    (char *)current) {
			// Merge the freed block with the previous block
			freed_block->size += sizeof(Node) + current->size;
			freed_block->next = current->next;
			break;
		}
		if (freed_block < current) {
			// Insert the freed block before the current block
			freed_block->next = current;
			head = freed_block;
			break;
		}
		current = current->next;
	}

	// If no merging or insertion occurred, just set the freed block as the head
	if (current == NULL) {
		freed_block->next = head;
		head = freed_block;
	}
}