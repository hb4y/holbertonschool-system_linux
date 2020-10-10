#ifndef SIG_H
#define SIG_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int handle_signal(void);
void (*current_handler_signal(void))(int);

#endif  /* SIG_H */
