#include "ls.h"

/**
 * process_input - Process de input options/dirs.
 * Description: Process entrys.
 * @argc: number of arguments passed to the ls
 * @argv: arguments passed to the ls
 * Return: char pointer with options and dirs
 **/
char *process_input(int argc, char *argv[])
{
	if (argc == 1)
	{
		execute(NULL, NULL);
		return (NULL);
	}
	else
	{
		(void) argv;
		(void) argc;
		return (NULL);
	}
}
