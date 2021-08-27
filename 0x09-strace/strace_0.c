#include "strace.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/register.h>

/**
 * proc_aux - aux process
 * @argc: argc
 * @argv: argc
 * @envp: env
 * Return: execv exit code
*/
int proc_aux(int argc, char *argv[], char *envp[])
{
	(void) argc;

	ptrace(PTRACE_TRACEME);

	kill(getpid(), SIGSTOP);

	return (execve(argv[0], argv, envp));
}

/**
 * wait - syscall sub
 * @sub_pro: PID
 * Return: 0 sub_pro success
*/
int wait(pid_t sub_pro)
{
	int stat;

	while (1)
	{
		ptrace(PTRACE_SYSCALL, sub_pro, 0, 0);
		waitpid(sub_pro, &stat, 0);
		if (WIFSTOPPED(stat) && WSTOPSIG(stat) & 0x80)
			return (0);
		if (WIFEXITED(stat))
			break;
	}
	return (1);
}

/**
 * trace - trace
 * @sub_pro: PID
 * Return: EXIT_SUCCESS
*/
int trace(pid_t sub_pro)
{
	int stat;
	long syscall;

	waitpid(sub_pro, &stat, 0);
	setbuf(stdout, NULL);

	ptrace(PTRACE_SETOPTIONS, sub_pro, 0, PTRACE_O_TRACESYSGOOD);
	while (1)
	{
		if (wait(sub_pro) != 0)
			break;
		syscall = ptrace(PTRACE_PEEKUSER, sub_pro, sizeof(long) * ORIG_RAX);
		fprintf(stdout, "%ld\n", syscall);
		if (wait(sub_pro) != 0)
			break;
	}
	return (EXIT_SUCCESS);
}

/**
 * main - main
 * @argc: argc
 * @argv: argv
 * @envp: env
 * Return: EXIT_SUCCESS
 */
int main(int argc, char *argv[], char *envp[])
{
	pid_t sub_pro;

	if (argc < 2)
	{
		fprintf(stderr, "%s command [args...]\n", argv[0]);
		return (EXIT_FAILURE);
	}

	sub_pro = fork();

	if (sub_pro < 0)
		return (EXIT_FAILURE);
	else if (sub_pro == 0)
		return (proc_aux(argc - 1, argv + 1, envp));
	else
		return (trace(sub_pro));

}
