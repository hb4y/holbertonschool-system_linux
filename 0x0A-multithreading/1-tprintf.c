#include "multithreading.h"

/**
 * tprintf - print out a given formatted string.
 * @format: string to print
 * Return: EXIT_SUCCESS
 */
int tprintf(char const *format, ...)
{
	printf("[%lu] %s", pthread_self(), format);

	return (EXIT_SUCCESS);

}
