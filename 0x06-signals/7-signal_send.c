#include "signals.h"

/**
* main -  sends the signal to a process (PID)
* @argc: arg count
* @argv: arg vector
* Return: EXIT_SUCCESS or EXIT_FAILURE
*/
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <pid>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	if (kill(atoi(argv[1]), SIGINT))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
