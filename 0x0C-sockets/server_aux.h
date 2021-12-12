#ifndef SERVER_AUX
#define SERVER_AUX

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

void print_error(char *s_error);
int get_req(char *req);
void respon(int socket_client, int status);

#endif
