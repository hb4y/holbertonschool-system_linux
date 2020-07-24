#ifndef LS_HEADER
#define LS_HEADER

#include <stdio.h>
#include <stdlib.h>

/**
 * struct car - linked list
 * @id: id of car
 * @n_laps: number of laps
 * @next: points to the next node
 *
 * Description: linked list car structure
 */
typedef struct car
{
	int id;
	int n_laps;
	struct car *next;
} car_n;

void join_race(int id, car_n **head);
void print_state(car_n **head);
void free_memory(car_n **head);
void race_state(int *id, size_t size);

#endif
