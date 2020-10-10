#include "signals.h"

/**
 * signal_c - handle Ctrl c
 * @sig: Signal
 */
void signal_c(int sig)
{
	printf("Gotcha! [%d]\n", sig);
	fflush(stdout);
}
/**
 * handle_sigaction - handler for the signal SIGINT
 * Return: 0 on success, or -1 on error
 */
int handle_sigaction(void)
{
	struct sigaction action;

	memset(&action, 0, sizeof(action));
	action.sa_handler = signal_c;
	return (sigaction(SIGINT, &action, NULL));
}
