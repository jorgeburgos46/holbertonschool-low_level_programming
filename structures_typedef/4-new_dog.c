#include <stdlib.h>
#include "dog.h"

/**
 * new_dog - creates a new dog
 * @name: name of the dog
 * @age: age of the dog
 * @owner: owner of the dog
 *
 * Return: pointer to new dog, or NULL if fail
 */
dog_t *new_dog(char *name, float age, char *owner)
{
	dog_t *dog;
	int i, len_name = 0, len_owner = 0;

	if (name == NULL || owner == NULL)
		return (NULL);

	while (name[len_name])
		len_name++;

	while (owner[len_owner])
		len_owner++;

	dog = malloc(sizeof(dog_t));
	if (dog == NULL)
		return (NULL);

	dog->name = malloc(len_name + 1);
	if (dog->name == NULL)
	{
		free(dog);
		return (NULL);
	}

	dog->owner = malloc(len_owner + 1);
	if (dog->owner == NULL)
	{
		free(dog->name);
		free(dog);
		return (NULL);
	}

	for (i = 0; i <= len_name; i++)
		dog->name[i] = name[i];

	for (i = 0; i <= len_owner; i++)
		dog->owner[i] = owner[i];

	dog->age = age;

	return (dog);
}
