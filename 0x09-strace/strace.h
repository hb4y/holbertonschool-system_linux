#ifndef LINUX_STRACE_H
#define LINUX_STRACE_H

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/user.h>
#include "syscalls.h"

char *read_s(pid_t sub_pro_pid, unsigned long addr);
void re_print(long ret, struct user_regs_struct ur);

#endif /* LINUX_STRACE_H */
