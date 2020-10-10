#include "signals.h"

/**
 * signal_quit - check PID of the quit signal
 * @sig: signal
 * @siginfo: struct of the signal
 * @context: ucontext_t
 */
void signal_quit(int sig, siginfo_t *siginfo, void *context)
{
	(void)sig;
	(void)context;

	printf("SIGQUIT sent by %d\n", siginfo->si_pid);
}

/**
 * trace_signal_sender - get quit signal info
 * Return: 0 on success, or -1 on error
 */

int trace_signal_sender(void)
{
	struct sigaction action;

	memset(&action, 0, sizeof(action));
	action.sa_flags |= SA_SIGINFO;
	action.sa_sigaction = signal_handler;
	return (sigaction(SIGQUIT, &act, NULL));
}
