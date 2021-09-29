#include "multithreading.h"

/**
 * thread_entry - thread entry
 * @arg: pointer to string
 * Return: void
 */
void *thread_entry(void *arg)
{
	printf("%s\n", (char *)arg);

	pthread_exit(NULL);

}
