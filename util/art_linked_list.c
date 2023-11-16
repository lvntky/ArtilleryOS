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
 * @brief insert node front of the list
 * 
 */
node_t *all_insert_front(art_linked_list_t *list, void *data)
{
	node_t *new_node = (node_t *)kmalloc(sizeof(node_t));

	if (new_node == NULL) {
		return NULL;
	}
	new_node->data = data;
	new_node->next = list->head;
	new_node->prev = NULL;

	if (list->head != NULL) {
		list->head->prev = new_node;
	} else {
		list->tail = new_node;
	}
	list->head = new_node;
	list->size++;

	return new_node;
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

void *all_remove_node(art_linked_list_t *list, node_t *node)
{
	void *data = node->data;

	if (node->prev != NULL) {
		node->next->prev = node->prev;
	} else {
		// if the node in the tail of the list
		list->tail = node->prev;
	}

	kfree(node);
	list->size--;

	return data;
}

void *all_remove_front(art_linked_list_t *list)
{
	if (list->head == NULL) {
		return NULL;
	}
	return all_remove_node(list, list->head);
}

void *all_remove_back(art_linked_list_t *list)
{
	if (list->head == NULL) {
		return NULL;
	}
	return all_remove_node(list, list->tail);
}

void all_push(art_linked_list_t *list, void *data)
{
	all_insert_front(list, data);
}

node_t *list_pop(art_linked_list_t *list)
{
	return all_remove_front(list);
}

void all_enqueue(art_linked_list_t *list, void *data)
{
	all_insert_back(list, data);
}

node_t *all_dequeue(art_linked_list_t *list)
{
	return all_remove_back(list);
}

void *all_peek_front(art_linked_list_t *list)
{
	if (list->head == NULL) {
		return NULL;
	}

	return list->head->data;
}

void *all_peek_back(art_linked_list_t *list)
{
	if (list->head == NULL) {
		return NULL;
	}

	return list->tail->data;
}

void all_full_destroy(art_linked_list_t *list)
{
	if (list == NULL) {
		return;
	}

	node_t *current = list->head;
	node_t *next;

	while (current != NULL) {
		next = current->next;
		kfree(current);
		current = next;
	}

	kfree(list);
}

void all_node_destroy(node_t *node)
{
}

bool all_does_contain(art_linked_list_t *list, void *data)
{
	if (list == NULL) {
		return false;
	}

	// Todo: ITERATE
	return false;
}
node_t *all_get_node_by_index(art_linked_list_t *list, int node_index)
{
	node_t *related_node = NULL;

	// TODO: do stuff
	return related_node;
}
void *all_remove_by_index(art_linked_list_t *list, int node_index)
{
	// TODO: do stuff;
	return NULL;
}
