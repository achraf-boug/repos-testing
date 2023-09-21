#include "shell.h"

/**
 * addTopNode - add a node at the top of the list
 * @h: the head of the list
 * @s: string to add to the list
 * @n: index history
 *
 * Return: the head of the list
 */
list_str *addTopNode(list_str **h, const char *s, int n)
{
	list_str *new;

	if (!h)
		return (NULL);
	new = malloc(sizeof(list_str));
	if (!new)
		return (NULL);
	setMem((void *)new, 0, sizeof(list_str));
	new->n = n;
	if (s)
	{
		new->s = _strcpy2(s);
		if (!new->s)
		{
			free(new);
			return (NULL);
		}
	}
	new->next = *h;
	*h = new;
	return (new);
}

/**
 * addNode - Adds a new node at the end of a linked list.
 * @h: Pointer to the pointer of the linked list's head.
 * @s: String value for the new node.
 * @n: Numeric value for the new node.
 *
 * Return: Pointer to the newly added node, or NULL on error.
 */
list_str *addNode(list_str **h, const char *s, int n)
{
	list_str *new, *node;

	if (!h)
		return (NULL);

	node = *h;
	new = malloc(sizeof(list_str));
	if (!new)
		return (NULL);
	setMem((void *)new, 0, sizeof(list_str));
	new->n = n;
	if (s)
	{
		new->s = _strcpy2(s);
		if (!new->s)
		{
			free(new);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
	else
		*h = new;
	return (new);
}

/**
 * showLinkedList - prints the strings of the list
 * @h: head of the list
 *
 * Return: size of list
 */
size_t showLinkedList(const list_str *h)
{
	size_t i = 0;

	while (h)
	{
		_putstr(h->s ? h->s : "(nil)");
		_putstr("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * rmNodeIndex - deletes node at given index
 * @h: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int rmNodeIndex(list_str **h, unsigned int index)
{
	list_str *node, *pnode;
	unsigned int i = 0;

	if (!h || !*h)
		return (0);

	if (!index)
	{
		node = *h;
		*h = (*h)->next;
		free(node->s);
		free(node);
		return (1);
	}
	node = *h;
	while (node)
	{
		if (i == index)
		{
			pnode->next = node->next;
			free(node->s);
			free(node);
			return (1);
		}
		i++;
		pnode = node;
		node = node->next;
	}
	return (0);
}

/**
 * flushLinkedList - frees the list
 * @h: head of the list
 *
 * Return: nothing
 */
void flushLinkedList(list_str **h)
{
	list_str *node, *nxnode, *head;

	if (!h || !*h)
		return;
	head = *h;
	node = head;
	while (node)
	{
		nxnode = node->next;
		free(node->s);
		free(node);
		node = nxnode;
	}
	*h = NULL;
}
