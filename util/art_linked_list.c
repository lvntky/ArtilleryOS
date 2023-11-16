#include "./include/art_linked_list.h"

/**
 * @brief creates an empty list sets
 * HEAD = NULL
 * TAIL = NULL
 * SIZE = 0
 * 
 * @return art_linked_list_t* 
 */
art_linked_list_t *all_create()
{
	art_linked_list_t *list = kmalloc(sizeof(art_linked_list_t));

	list->head = NULL;
	list->tail = NULL;
	list->size = 0;

	return list;
}
uint32_t all_size(art_linked_list_t *list)
{
	if (!list) {
		return 0;
	}
	return list->size;
}

/**
 * @brief insert node at back of list
 * 
 */
void all_insert_back(art_linked_list_t *list, void *data)
{
	node_t *new_node = (node_t *)kmalloc(sizeof(node_t));

	if (new_node == NULL) {
		qemu_write_string("%s Memory allocation failed for new_node\n",
				  NEGATIVE_OUTPUT);
	}
	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = NULL;

	if (list->head == NULL) {
		list->head = new_node;
		list->tail = new_node;
	} else {
		new_node->prev = list->tail;
		list->tail->next = new_node;
		list->tail = new_node;
	}
	list->size++;
}

void all_print_int_data(void *data)
{
	qemu_write_string("%d -> ", *(int *)data);
}