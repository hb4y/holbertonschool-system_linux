#include "signals.h"

/**
 * signal_c - Catch SIGINT
 * @signal: the signal
 */
void signal_c(int sig)
{
	printf("Gotcha! [%d]\n", sig);
	fflush(stdout);
}

/**
 * handle_signal -handle ctrl c
 * Return: 0 on success
 */
int handle_signal(void)
{
	if (signal(SIGINT, signal_c) == SIG_ERR)
		return (-1);
	return (0);
}
