#include "signals.h"

/**
 * current_handler_signal - current handler of SIGINT
 * Return: Return handler or NULL
 */
void (*current_handler_signal(void))(int)
{
	void (*sig)(int);

	sig = signal(SIGINT, NULL);
	signal(SIGINT, sig);

	return (sig);
}
