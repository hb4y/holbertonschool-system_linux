#include "signals.h"

/**
 * current_handler_signal - current handler of SIGINT
 * Return: Return handler or NULL
 */
void (*current_handler_signal(void))(int)
{
	return (signal(SIGINT, signal(SIGINT, NULL)));
}
