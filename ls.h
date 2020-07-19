#ifndef LS_HEADER
#define LS_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>

char *process_input(int argc, char *argv[]);
void execute(char *options, char **to_read);

#endif
