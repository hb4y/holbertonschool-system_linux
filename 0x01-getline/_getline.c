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
		if (current->read && current->line)
		{
			free(current->line);
			current->line = NULL;
		}
		free(current);
		current = NULL;
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

	if (!head || !*head)
		return (NULL);

	for (current = *head; current; current = current->next)
	{
		if (current->end)
		{
			free_all(*head);
			return (NULL);
		}
		if (current->fd == fd && current->read)
		{
			if (!current->next || (current->next && (current->next)->fd != fd))
				if (current->end)
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

line_n *create_node(line_n **head, int fd, char *line, int end)
{
	line_n *new, *current;

	current = *head;
	new = malloc(sizeof(line_n));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->read = 1;
	new->end = end;
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
	char buf[READ_SIZE], *line, end;
	int n, full, i, j;

	line = NULL;
	end = full = 0;

	if (fd == -1)
	{
		free_all(head);
		head = NULL;
		return (NULL);
	}

	memset(buf, '\0', READ_SIZE);
	n = read(fd, buf, READ_SIZE);

	for (; n > 0; n = read(fd, buf, READ_SIZE))
	{
		full += n;
		for (i = j = 0; j <= READ_SIZE; j++)
		{
			if (j == full || buf[j] == '\n')
			{
				line = malloc(((j - i) + 1) * sizeof(char));
				if (!line)
					return (NULL);
				memset(line, '\0', (j - i) + 1);
				memcpy(line, &buf[i], (j - i));
				if (j == full)
					end = 1;
				create_node(&head, fd, line, end);
				i = j + 1;
			}
		}
	}
	return (get_line(&head, fd));
}
