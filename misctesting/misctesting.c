#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 1024

typedef struct Node {
    size_t size;
    struct Node* next;
} Node;

static char memory[MEMORY_SIZE];
static Node* head = NULL;

void* malloc_custom(size_t size) {
    if (size == 0)
        return NULL;

    // Align size to the size of a Node
    size_t aligned_size = (size + sizeof(Node) - 1) / sizeof(Node) * sizeof(Node);
    
    Node* current = head;
    Node* previous = NULL;

    while (current != NULL) {
        if (current->size >= aligned_size) {
            // Found a block big enough
            if (current->size > aligned_size + sizeof(Node)) {
                // Split the block
                Node* new_node = (Node*)((char*)current + aligned_size + sizeof(Node));
                new_node->size = current->size - aligned_size - sizeof(Node);
                new_node->next = current->next;
                current->next = new_node;
            }
            if (previous != NULL) {
                previous->next = current->next;
            } else {
                head = current->next;
            }
            return (char*)current + sizeof(Node);
        }
        previous = current;
        current = current->next;
    }

    // No suitable block found, allocate new memory
    Node* new_node = (Node*)memory;
    if (MEMORY_SIZE < aligned_size + sizeof(Node)) {
        // Memory is insufficient
        return NULL;
    }
    new_node->size = MEMORY_SIZE - sizeof(Node);
    new_node->next = NULL;
    if (MEMORY_SIZE > aligned_size + sizeof(Node)) {
        // Split the block
        Node* remaining_memory = (Node*)((char*)new_node + aligned_size + sizeof(Node));
        remaining_memory->size = MEMORY_SIZE - aligned_size - sizeof(Node);
        remaining_memory->next = NULL;
        new_node->next = remaining_memory;
    }
    head = new_node;
    return (char*)new_node + sizeof(Node);
}

void free_custom(void* ptr) {
    if (ptr == NULL)
        return;

    Node* freed_block = (Node*)((char*)ptr - sizeof(Node));
    Node* current = head;

    // Find the correct position to insert the freed block
    while (current != NULL) {
        if ((char*)current + current->size + sizeof(Node) == (char*)freed_block) {
            // Merge the freed block with the next block
            current->size += sizeof(Node) + freed_block->size;
            freed_block = current;
            break;
        }
        if ((char*)freed_block + freed_block->size + sizeof(Node) == (char*)current) {
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

int main() {
    // Example usage
    int* ptr1 = malloc_custom(10 * sizeof(int));
    double* ptr2 = malloc_custom(5 * sizeof(double));

    printf("Pointer 1: %p\n", (void*)ptr1);
    printf("Pointer 2: %p\n", (void*)ptr2);

    free_custom(ptr1);
    free_custom(ptr2);

    return 0;
}
