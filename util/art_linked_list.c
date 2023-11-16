#include "./include/art_linked_list.h"

node_t *all_create_node(void *data)
{
	node_t *new_node = (node_t *)kmalloc(sizeof(node_t));
	if (new_node != NULL) {
		new_node->data = data;
		new_node->next = NULL;
	}
	return new_node;
}