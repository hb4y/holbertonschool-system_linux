#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**              
 * main - creates a string in the heap and prints               
 * Return: EXIT_FAILURE if malloc failed. Or inf loop.
 */
int main(void)
{
	char *s;
	unsigned long int i;

	s = strdup("InTheHeap");
	if (s == NULL)
	{
	  fprintf(stderr, "Error allocating men\n");
	  return (EXIT_FAILURE);
	}

	i = 0;
	while (s)
	{
	  printf("[%lu] %s (%p)\n", i, s, (void *)s);
	  sleep(1);
	  i++;
	}
	return (EXIT_SUCCESS);
}