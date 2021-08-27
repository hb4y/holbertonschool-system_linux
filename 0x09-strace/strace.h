#ifndef LINUX_STRACE_H
#define LINUX_STRACE_H

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/register.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/user.h>
#include "syscalls.h"

char *read_string(pid_t sub_pro_pid, unsigned long addr);
void print_retval(long retval, struct user_regs_struct ur);

#endif /* LINUX_STRACE_H */
