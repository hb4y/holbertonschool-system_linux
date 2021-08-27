#include "strace.h"
#include "syscalls.h"

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
 * @ur: user struct
 * @index: index
 * @register: register
 * @str: separator
 * @sub_pro_pid: PID subpro
*/
void aux_print(struct user_regs_struct ur, int index, ulong register,
		    char *str, pid_t sub_pro_pid)
{
	char *s = NULL;

	if (syscalls_64_g[ur.orig_rax].params[index] != (type_t)-1 &&
	    syscalls_64_g[ur.orig_rax].params[index] != VOID)
	{
		if (syscalls_64_g[ur.orig_rax].params[index] == VARARGS)
			fprintf(stdout, "%s...", str);
		else if (syscalls_64_g[ur.orig_rax].params[index] == CHAR_P)
		{
			s = read_s(sub_pro_pid, register);
			fprintf(stdout, "%s\"%s\"", str, s);
			free(s);
		}
		else if (syscalls_64_g[ur.orig_rax].params[index] == INT)
			fprintf(stdout, "%s%d", str, (int)register);
		else if (syscalls_64_g[ur.orig_rax].params[index] == LONG)
			fprintf(stdout, "%s%ld", str, (long)register);
		else if (syscalls_64_g[ur.orig_rax].params[index] == SIZE_T)
			fprintf(stdout, "%s%lu", str, (ulong)register);
		else if (syscalls_64_g[ur.orig_rax].params[index] == SSIZE_T)
			fprintf(stdout, "%s%ld", str, (long)register);
		else if (syscalls_64_g[ur.orig_rax].params[index] == U64)
			fprintf(stdout, "%s%lu", str, (ulong)register);
		else if (syscalls_64_g[ur.orig_rax].params[index] == UINT32_T)
			fprintf(stdout, "%s%lu", str, (ulong)register);
		else if (syscalls_64_g[ur.orig_rax].params[index] == UNSIGNED_INT)
			fprintf(stdout, "%s%u", str, (uint)register);
		else if (syscalls_64_g[ur.orig_rax].params[index] == UNSIGNED_LONG)
			fprintf(stdout, "%s%lu", str, (ulong)register);
		else if (syscalls_64_g[ur.orig_rax].params[index] == PID_T)
			fprintf(stdout, "%s%d", str, (int)register);
		else
			fprintf(stdout, "%s%#lx", str, register);
	}
}

/**
 * print_two - print
 * @ur: user struct
 * @sub_pro_pid: PID subpro
 */
void print_two(struct user_regs_struct ur, pid_t sub_pro_pid)
{
	aux_print(ur, 0, ur.rdi, "", sub_pro_pid);
	aux_print(ur, 1, ur.rsi, ", ", sub_pro_pid);
	aux_print(ur, 2, ur.rdx, ", ", sub_pro_pid);
	aux_print(ur, 3, ur.r10, ", ", sub_pro_pid);
	aux_print(ur, 4, ur.r8, ", ", sub_pro_pid);
	aux_print(ur, 5, ur.r9, ", ", sub_pro_pid);

}

/**
 * trace - trace process
 * @sub_pro: subprocess PID
 * @argc: arg count
 * @argv: argument vector
 * @envp: environmental variables
 * Return: EXIT_SUCCESS on success
 */
int trace(pid_t sub_pro, int argc, char *argv[], char *envp[])
{
	int stat, i;
	long ret;
	struct user_regs_struct ur;

	setbuf(stdout, NULL);
	waitpid(sub_pro, &stat, 0);
	ptrace(PTRACE_SETOPTIONS, sub_pro, 0, PTRACE_O_TRACESYSGOOD);

	if (wait(sub_pro) != 0)
		return (0);

	ptrace(PTRACE_GETREGS, sub_pro, 0, &ur);
	if (wait(sub_pro) != 0)
		return (0);

	ret = ptrace(PTRACE_PEEKUSER, sub_pro, sizeof(long) * RAX);
	fprintf(stdout, "execve(\"%s\", [", argv[0]);
	for (i = 0; i < argc; ++i)
		printf("%s\"%s\"", i == 0 ? "" : ", ", argv[i]);
	for (i = 0; envp[i]; ++i)
		;
	printf("], [/* %d vars */]) = %#lx\n", i, ret);
	while (1)
	{
		if (wait(sub_pro) != 0)
			break;

		ptrace(PTRACE_GETREGS, sub_pro, 0, &ur);
		fprintf(stdout, "%s(", syscalls_64_g[ur.orig_rax].name);
		print_two(ur, sub_pro);
		if (wait(sub_pro) != 0)
			break;

		ret = ptrace(PTRACE_PEEKUSER, sub_pro, sizeof(long) * RAX);
		re_print(ret, ur);
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
	--argc;
	if (sub_pro < 0)
		return (EXIT_FAILURE);
	if (sub_pro == 0)
	{
		ptrace(PTRACE_TRACEME);
		kill(getpid(), SIGSTOP);
		return (execve(argv[0], argv, envp));
	}
	else
		return (trace(sub_pro, argc, argv, envp));
}
