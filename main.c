#include "ls.h"

/**
 * main - Main entry function.
 * Description: main funtion for ls.
 * @argc: number of arguments passed to the ls
 * @argv: arguments passed to the 'ls'
 * Return: 0 on success
 **/

int main(int argc, char *argv[])
{
	if (argc)
	{
		char *operation = process_input(argc, argv);
		(void) operation;
		/*#execute*/

		return (0);
	}
	return (1);
}
