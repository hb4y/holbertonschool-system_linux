#include "strace.h"
#include "syscalls.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/register.h>

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
 * aux_print - print
 * @ur: user register
 * @index: index
 * @register: register
 * @str: separator
*/
void aux_print(struct user_regs_struct ur,
		    int index, ulong register, char *str)
{
	if (syscalls_64_g[ur.orig_rax].params[index] != (type_t)-1 &&
	    syscalls_64_g[ur.orig_rax].params[index] != VOID)
	{
		if (syscalls_64_g[ur.orig_rax].params[index] == VARARGS)
			fprintf(stdout, "%s...", str);
		else
			fprintf(stdout, "%s%#lx", str, register);
	}
}

/**
 * print_two - print arg
 * @ur: user struct
*/
void print_two(struct user_regs_struct ur)
{
	aux_print(ur, 0, ur.rdi, "");
	aux_print(ur, 1, ur.rsi, ", ");
	aux_print(ur, 2, ur.rdx, ", ");
	aux_print(ur, 3, ur.r10, ", ");
	aux_print(ur, 4, ur.r8, ", ");
	aux_print(ur, 5, ur.r9, ", ");

}

/**
 * trace - trace
 * @sub_pro: PID
 * Return: EXIT_SUCCESS
*/
int trace(pid_t sub_pro)
{
	int stat;
	struct user_regs_struct ur;

	waitpid(sub_pro, &stat, 0);
	ptrace(PTRACE_SETOPTIONS, sub_pro, 0, PTRACE_O_TRACESYSGOOD);
	if (wait(sub_pro) != 0)
		return (EXIT_SUCCESS);

	ptrace(PTRACE_GETREGS, sub_pro, 0, &ur);
	if (wait(sub_pro) != 0)
		return (EXIT_SUCCESS);

	ptrace(PTRACE_GETREGS, sub_pro, 0, &ur);
	fprintf(stdout, " = %#lx\n", (ulong)ur.rax);

	while (1)
	{
		if (wait(sub_pro) != 0)
			break;
		ptrace(PTRACE_GETREGS, sub_pro, 0, &ur);
		fprintf(stdout, "%s(", syscalls_64_g[ur.orig_rax].name);
		print_two(ur);
		if (wait(sub_pro) != 0)
			break;
		ptrace(PTRACE_GETREGS, sub_pro, 0, &ur);
		fprintf(stdout, ") = %#lx\n", (ulong)ur.rax);
	}

	fprintf(stdout, ") = ?\n");
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
	++argv;
	if (sub_pro == 0)
	{
		ptrace(PTRACE_TRACEME);
		kill(getpid(), SIGSTOP);
		return (execve(argv[0], argv, envp));
	}
	else
	{
		setbuf(stdout, NULL);
		fprintf(stdout, "execve(%p, %p, %p)", (void *)argv[0],
			(void *)argv, (void *)envp);
		return (trace(sub_pro));
	}
}
