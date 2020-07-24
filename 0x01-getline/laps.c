#include "laps.h"

/**
 * join_race - join new cars to the race.
 * Description: join new cars to the race.
 * @id: car id
 * @head: head of the list
 * Return: void
 **/

void join_race(int id, car_n **head)
{
	car_n *search, *new;

	new = malloc(sizeof(car_n));

	if (!new)
		return;

	new->id = id;
	new->n_laps = -1;
	new->next = NULL;

	if (!head || !(*head))
	{
		*head = new;
		printf("Car %i joined the race\n", id);
		return;
	}

	for (search = *head; search->next != NULL; search = search->next)
	{
		if (search->id == id)
		{
			free(new);
			return;
		}
	}
	if (search->id == id)
	{
		free(new);
		return;
	}

	search->next = new;

	printf("Car %i joined the race\n", id);
}

/**
 * print_state - print the current state of the race.
 * Description: print the current state of the race.
 * @head: head of the list
 * Return: void
 **/

void print_state(car_n **head)
{
	car_n *search;

	for (search = *head; search->next != NULL; search = search->next)
	{
		search->n_laps = search->n_laps + 1;
		printf("Car %i [%i laps]\n", search->id, search->n_laps);
	}
	search->n_laps = search->n_laps + 1;
	printf("Car %i [%i laps]\n", search->id, search->n_laps);
}

/**
 * free_memory - free all the list.
 * Description: free all the list.
 * @head: head of the list
 * Return: void
 **/

void free_memory(car_n **head)
{
	car_n *current, *prev;

	if (head == NULL || *head == NULL)
		return;

	current = prev = *head;

	while (current)
	{
		prev = current;
		current = current->next;
		free(prev);
	}
}

/**
 * race_state - return the race state.
 * Description: print Car <id> [# of laps].
 * @id: array of all the id of the cars in race
 * @size: size of *id
 * Return: void
 **/

void race_state(int *id, size_t size)
{
	static car_n *head;
	size_t i;

	if (!size)
	{
		free_memory(&head);
		return;
	}

	for (i = 0; i < size; i++)
		join_race(*(id + i), &head);

	printf("Race state:\n");
	print_state(&head);
}
