#include "signals.h"

/**
* signal_func - func to print signal number
* @sig: signal
*/
void signal_func(int sig)
{
	printf("Caught %d\n", sig);
}

/**
* main - recive and handle signal
* Return: EXIT_SUCCESS
*/
int main(void)
{
	struct sigaction action;

	action.sa_handler = signal_func;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(SIGINT, &action, NULL);
	pause();
	printf("Signal received\n");
	return (EXIT_SUCCESS);
}
