#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
 *  main - Read ELF info
 * @argc: argv counter
 * @argv: arguments
 * @env: system env
 * Return: sucess or failure code status
 */

int main(int argc, char **argv, char **env)
{
	char *newargv[] = {"/usr/bin/readelf", "-W", "-s", ""};

	(void) argc;
	newargv[3] = argv[1];

	if (execve("/usr/bin/readelf", newargv, env) != -1)
		return (EXIT_SUCCESS);
	perror("Something went wrong");
	return (EXIT_FAILURE);
}
