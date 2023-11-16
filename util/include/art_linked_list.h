/**
 * @file art_linked_list.h
 * @author levent kaya
 * @brief Artillery OS Linked List UTIL
 * @version 0.1
 * @date 2023-11-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _ART_LINKED_LIST_H_
#define _ART_LINKED_LIST_H_

#include "../util.h"
#include <stdint.h>

typedef struct node {
	void *data;
	struct node *next;
	struct node *prev;

} node_t;

typedef struct art_linked_list {
	node_t *head;
	node_t *tail;
	uint32_t size;
} art_linked_list_t;

#define FOREACH(n, list) for (node_t *n = list->head; n != NULL; n = n->next)

art_linked_list_t *all_create();
uint32_t all_size(art_linked_list_t *);
node_t *all_insert_front(art_linked_list_t *, void *);
void all_insert_back(art_linked_list_t *, void *);
void *all_remove_node(art_linked_list_t *, node_t *);
void *all_remove_front(art_linked_list_t *);
void *all_remove_back(art_linked_list_t *);
void all_push(art_linked_list_t *, void *);
node_t *list_pop(art_linked_list_t *);
void all_enqueue(art_linked_list_t *, void *);
node_t *all_dequeue(art_linked_list_t *);
void *all_peek_front(art_linked_list_t *);
void *all_peek_back(art_linked_list_t *);
void all_destroy(art_linked_list_t *);
void all_node_destroy(node_t *);
int all_does_contain(art_linked_list_t *, void *);
node_t *all_get_node_by_index(art_linked_list_t *, int);
void *all_remove_by_index(art_linked_list_t *, int);
void all_print_int_data(void *);

#endif