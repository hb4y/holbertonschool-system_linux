#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - GNU nm command
 * @argc: Arguments count
 * @argv: Arguments
 * @env: Environment
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */

int main(int argc, char **argv, char **env)
{
	char *av[] = {"./hnm", "-sf", "", NULL};

	(void)argc;

	av[2] = argv[1];

	if (execve("/usr/bin/nm", av, env) == -1)
	{
		perror("execv");

		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}
