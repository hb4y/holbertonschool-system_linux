#include "signals.h"

/**
* current_handler_sigaction - handler of the signal SIGINT
* Return: pointer to the current handler of SIGINT, or NULL on failure
*/
void (*current_handler_sigaction(void))(int)
{
	struct sigaction action;

	if (sigaction(SIGINT, NULL, &action) != -1)
		return (action.sa_handler);
	return (NULL);
}
