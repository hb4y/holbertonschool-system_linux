#ifndef LS_HEADER
#define LS_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define READ_SIZE 1024

/**
 * struct car - linked list
 * @id: id of car
 * @n_laps: number of laps
 * @run: 1 if make a lap 0 if not
 * @next: points to the next node
 *
 * Description: linked list car structure
 */
typedef struct line
{
	int fd;
	short int read;
	char *line;
	struct line *next;
} line_n;

char *get_line(line_n **head, int fd);
line_n *create_node(line_n **head, int fd, char *line);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_getline(const int fd);

#endif