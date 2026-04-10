#include "hash_tables.h"
#include <stdlib.h>
#include <string.h>

/**
 * create_node - creates a new hash node
 * @key: the key string
 * @value: the value string
 *
 * Return: pointer to new node, or NULL on failure
 */
hash_node_t *create_node(const char *key, const char *value)
{
	hash_node_t *new_node;

	new_node = malloc(sizeof(hash_node_t));
	if (new_node == NULL)
		return (NULL);

	new_node->key = strdup(key);
	if (new_node->key == NULL)
	{
		free(new_node);
		return (NULL);
	}

	new_node->value = strdup(value);
	if (new_node->value == NULL)
	{
		free(new_node->key);
		free(new_node);
		return (NULL);
	}

	new_node->next = NULL;
	return (new_node);
}

/**
 * hash_table_set - adds an element to the hash table
 * @ht: pointer to the hash table
 * @key: the key (cannot be empty)
 * @value: the value associated with key (will be duplicated)
 *
 * Return: 1 if succeeded, 0 otherwise
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
	unsigned long int index;
	hash_node_t *new_node, *current;
	char *value_dup;

	if (ht == NULL || key == NULL || *key == '\0')
		return (0);

	index = key_index((const unsigned char *)key, ht->size);

	for (current = ht->array[index]; current; current = current->next)
	{
		if (strcmp(current->key, key) == 0)
		{
			value_dup = strdup(value);
			if (value_dup == NULL)
				return (0);
			free(current->value);
			current->value = value_dup;
			return (1);
		}
	}

	new_node = create_node(key, value);
	if (new_node == NULL)
		return (0);

	new_node->next = ht->array[index];
	ht->array[index] = new_node;
	return (1);
}
