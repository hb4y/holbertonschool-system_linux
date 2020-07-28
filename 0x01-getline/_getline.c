#include "_getline.h"

/**
 * free_all - free all alocated and zero the statics.
 * Description: free all alocated and zero the statics.
 * @head: head of list.
 * Return: return pointer to line.
 **/

void free_all(line_n *head)
{
	line_n *current;

	while (head)
	{
		current = head;
		head = head->next;
		if (current->line)
			free(current->line);
		free_all(current);
	}
}

/**
 * get_line - return 1 line.
 * Description: return 1 line.
 * @head: head of list.
 * @fd: file descriptor.
 * Return: return pointer to line.
 **/

char *get_line(line_n **head, int fd)
{
	line_n *current;
	char *l;

	if (!head || !*head)
		return (NULL);

	for (current = *head; current; current = current->next)
	{
		if (current->fd == fd && current->read)
		{
			l = current->line;
			if (!current->next || (current->next && (current->next)->fd != fd))
				if (l &&  !l[0] && !l[1])
					return (NULL);
			current->read = 0;
			return (current->line);
		}
	}
	return (NULL);
}

/**
 * create_node - create node with line.
 * Description: create node with line.
 * @head: head of list.
 * @fd: file descriptor.
 * @line: line from file.
 * Return: return pointer to new node
 **/

line_n *create_node(line_n **head, int fd, char *line)
{
	line_n *new, *current;

	current = *head;
	new = malloc(sizeof(line_n));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->read = 1;
	new->line = line;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (new);
}
/**
 * _getline - read line from file descriptor.
 * Description: read line from file descriptor.
 * @fd: file descriptor
 * Return: lines read from file descriptor
 **/

char *_getline(const int fd)
{
	static line_n *head;
	char buf[READ_SIZE], *line;
	int n, full, i, j;

	line = NULL;
	full = 0;

	memset(buf, '\0', READ_SIZE);
	n = read(fd, buf, READ_SIZE);

	if (fd == -1)
		free_all(head);
	for (; n > 0 && !head; n = read(fd, buf, READ_SIZE))
	{
		full += n;
		for (i = j = 0; j <= READ_SIZE; j++)
		{
			if (buf[j] == '\n' || j == full)
			{
				line = malloc(((j - i) + 1) * sizeof(char));
				if (!line)
					return (NULL);
				memset(line, '\0', (j - i) + 1);
				memcpy(line, &buf[i], (j - i));
				create_node(&head, fd, line);
				i = j + 1;
			}
		}
	}
	return (get_line(&head, fd));
}
