#ifndef LS_HEADER
#define LS_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define READ_SIZE 1024

/**
 * struct line - linked list
 * @fd: file descriptor
 * @read: is to be read? 1 yes 0 no
 * @line: line to read
 * @next: points to the next node
 * Description: linked list of lines
 */
typedef struct line
{
	int fd;
	short int read;
	short int end;
	char *line;
	struct line *next;
} line_n;

char *get_line(line_n **head, int fd);
line_n *create_node(line_n **head, int fd, char *line, int end);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_getline(const int fd);

#endif
