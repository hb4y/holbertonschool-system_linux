#include "strace.h"

/**
 * read_s - string
 * @sub_pro_pid: pid
 * @addr: address
 * Return: pointer
 */
char *read_s(pid_t sub_pro_pid, unsigned long addr)
{
	char *str = malloc(4096);
	unsigned int alloc = 4096;
	unsigned long read = 0;
	unsigned long tmp;

	while (1)
	{
		if (read + sizeof(tmp) > alloc)
		{
			alloc *= 2;
			str = realloc(str, alloc);
		}
		tmp = ptrace(PTRACE_PEEKDATA, sub_pro_pid, addr + read);
		if (errno != 0)
		{
			str[read] = 0;
			break;
		}
		memcpy(str + read, &tmp, sizeof(tmp));
		if (memchr(&tmp, 0, sizeof(tmp)) != NULL)
			break;
		read += sizeof(tmp);
	}

	return (str);

}

/**
 * re_print - print
 * @ret: return val
 * @ur: user struct
 */
void re_print(long ret, struct user_regs_struct ur)
{
	char *str = ") = ";

	if (syscalls_64_g[ur.orig_rax].ret == INT)
		fprintf(stdout, "%s%d\n", str, (int)ret);
	else if (syscalls_64_g[ur.orig_rax].ret == LONG)
		fprintf(stdout, "%s%ld\n", str, (long)ret);
	else if (syscalls_64_g[ur.orig_rax].ret == SIZE_T)
		fprintf(stdout, "%s%lu\n", str, (ulong)ret);
	else if (syscalls_64_g[ur.orig_rax].ret == SSIZE_T)
		fprintf(stdout, "%s%ld\n", str, (long)ret);
	else if (syscalls_64_g[ur.orig_rax].ret == U64)
		fprintf(stdout, "%s%lu\n", str, (ulong)ret);
	else if (syscalls_64_g[ur.orig_rax].ret == UINT32_T)
		fprintf(stdout, "%s%lu\n", str, (ulong)ret);
	else if (syscalls_64_g[ur.orig_rax].ret == UNSIGNED_INT)
		fprintf(stdout, "%s%u\n", str, (uint)ret);
	else if (syscalls_64_g[ur.orig_rax].ret == UNSIGNED_LONG)
		fprintf(stdout, "%s%lu\n", str, (ulong)ret);
	else if (syscalls_64_g[ur.orig_rax].ret == PID_T)
		fprintf(stdout, "%s%d\n", str, (int)ret);
	else
		fprintf(stdout, "%s%#lx\n", str, ret);

}
