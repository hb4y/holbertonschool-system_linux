#include "_getline.h"

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

	if (!head || !*head)
		return (NULL);

	for (current = *head; current; current = current->next)
	{
		if (current->fd == fd && current->read)
		{
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

	for (; n > 0 && !head; n = read(fd, buf, READ_SIZE))
	{
		full += n;
		for (i = j = 0; j < READ_SIZE; j++)
		{
			if (buf[j] == '\n' || j == full)
			{
				line = malloc((j - i) * sizeof(char));
				if (!line)
					return (NULL);
				memset(line, '\0', (j - i));
				strncpy(line, &buf[i], (j - i));
				line[(j - i)] = '\0';
				create_node(&head, fd, line);
				printf("::[%s]::", line);
				i = j + 1;
			}
		}
	}
	return (get_line(&head, fd));
}
