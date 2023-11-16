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

typedef struct node {
	void *data;
	struct node *next;

} __attribute__((packed)) node_t;

typedef struct art_linked_list {
	node_t *head;
} __attribute__((packed)) art_linked_list_t;

node_t *all_create_node(void *);
void all_initialize_list(art_linked_list_t *);
void all_insert_at_beggining(art_linked_list_t *, void *);
void all_display_list(art_linked_list_t *, void (*display_func)(void *));
void all_free_list(art_linked_list_t *);

#endif