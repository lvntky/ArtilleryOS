#ifndef _STDLIB_H_
#define _STDLIB_H_

#include "inttypes.h"

#define MEMORY_SIZE 1024

typedef struct Node {
    unsigned long long size;
    struct Node* next;
} Node;

extern char memory[MEMORY_SIZE];
extern Node *head;

int abs(int);
void srand(short seed);
int rand(int min, int max);

/**
 * @brief Allocates size bytes of uninitialized storage.
 * 
 * If allocation succeeds, returns a pointer that is suitably aligned
 * for any object type with fundamental alignment.
 * 
 * If size is zero, the behavior of malloc is implementation-defined.
 * For example, a null pointer may be returned. Alternatively, a non-null
 * pointer may be returned; but such a pointer should not be dereferenced,
 * and should be passed to free to avoid memory leaks.
 * 
 * malloc is thread-safe: it behaves as though only accessing the memory
 * locations visible through its argument, and not any static storage.
 * 
 * A previous call to free or realloc that deallocates a region of memory
 * synchronizes-with a call to malloc that allocates the same or a part of
 * the same region of memory. This synchronization occurs after any access
 * to the memory by the deallocating function and before any access to the
 * memory by malloc. There is a single total order of all allocation and
 * deallocation functions operating on each particular region of memory.
 * 
 * (since C11)
 * 
 * @param size  Size of memory block to allocate, in bytes.
 * @return void* Pointer to the allocated memory block, or NULL if allocation fails.
 */
void *malloc(unsigned long long size);

/**
 * @brief Allocates memory for an array of num objects of size and initializes all bytes
 *        in the allocated storage to zero.
 * 
 * If allocation succeeds, returns a pointer to the lowest (first) byte in the allocated
 * memory block that is suitably aligned for any object type with fundamental alignment.
 * 
 * If size is zero, the behavior is implementation defined (null pointer may be returned,
 * or some non-null pointer may be returned that may not be used to access storage).
 * 
 * calloc is thread-safe: it behaves as though only accessing the memory locations visible
 * through its argument, and not any static storage.
 * 
 * A previous call to free or realloc that deallocates a region of memory synchronizes-with
 * a call to calloc that allocates the same or a part of the same region of memory. This
 * synchronization occurs after any access to the memory by the deallocating function and
 * before any access to the memory by calloc. There is a single total order of all
 * allocation and deallocation functions operating on each particular region of memory.
 * 
 * (since C11)
 * 
 * @param num   Number of objects to allocate memory for.
 * @param size  Size of each object, in bytes.
 * @return void* Pointer to the allocated memory block, or NULL if allocation fails.
 */
void *calloc(unsigned long long num_elements, unsigned long long element_size);

/**
 * @brief Reallocates the given area of memory.
 * 
 * If ptr is not NULL, it must be previously allocated by malloc, calloc or realloc
 * and not yet freed with a call to free or realloc. Otherwise, the results are undefined.
 * 
 * The reallocation is done by either:
 * 
 * a) expanding or contracting the existing area pointed to by ptr, if possible.
 *    The contents of the area remain unchanged up to the lesser of the new and old sizes.
 *    If the area is expanded, the contents of the new part of the array are undefined.
 * 
 * b) allocating a new memory block of size new_size bytes,
 *    copying memory area with size equal to the lesser of the new and the old sizes,
 *    and freeing the old block.
 * 
 * If there is not enough memory, the old memory block is not freed and null pointer is returned.
 * 
 * If ptr is NULL, the behavior is the same as calling malloc(new_size).
 * 
 * @param ptr       Pointer to the memory area to be reallocated.
 * @param new_size  New size for the memory block, in bytes.
 * @return void*    Pointer to the reallocated memory area, or NULL if reallocation fails.
 */
void *realloc(void *ptr, unsigned long long new_size);


/**
 * @brief Deallocates the space previously allocated by malloc(), calloc(),
 *        aligned_alloc(), or realloc() (since C11).
 * 
 * If ptr is a null pointer, the function does nothing.
 * 
 * The behavior is undefined if the value of ptr does not equal a value returned
 * earlier by malloc(), calloc(), realloc(), or aligned_alloc()(since C11).
 * 
 * The behavior is undefined if the memory area referred to by ptr has already been
 * deallocated, that is, free(), free_sized(), free_aligned_sized()(since C23), or
 * realloc() has already been called with ptr as the argument and no calls to malloc(),
 * calloc(), realloc(), or aligned_alloc()(since C11) resulted in a pointer equal to ptr
 * afterwards.
 * 
 * The behavior is undefined if after free() returns, an access is made through the
 * pointer ptr (unless another allocation function happened to result in a pointer
 * value equal to ptr).
 * 
 * free is thread-safe: it behaves as though only accessing the memory locations visible
 * through its argument, and not any static storage.
 * 
 * A call to free that deallocates a region of memory synchronizes-with a call to any
 * subsequent allocation function that allocates the same or a part of the same region
 * of memory. This synchronization occurs after any access to the memory by the deallocating
 * function and before any access to the memory by the allocation function. There is a
 * single total order of all allocation and deallocation functions operating on each
 * particular region of memory.
 * 
 * (since C11)
 * 
 * @param ptr Pointer to the memory area to deallocate.
 */
void free(void *ptr);



#endif
