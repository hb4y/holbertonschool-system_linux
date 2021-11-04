#include "server.h"

/**
 * print_error - print error
 * @s_error: error
 */
void print_error(char *s_error)
{
	printf("%s\n", s_error);
	exit(EXIT_FAILURE);
}

/**
 * main - listen
 * @argc: argc
 * @argv: argv
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	int socket_a = 0;
	int size = 0;
	int port = 0;
	struct sockaddr_in addr_server;
	char *host = NULL;
	char aux[128] = {0};

	if (argc != 3)
	{
		sprintf(aux, "Usage: %s <host> <port>", argv[0]);
		print_error(aux);
	}
	host = argv[1];
	port = atoi(argv[2]);
	socket_a = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socket_a == -1)
		print_error("socket failed");
	addr_server.sin_family = AF_INET;
	addr_server.sin_port = htons(port);
	addr_server.sin_addr.s_addr = strcmp("localhost", host) ? inet_addr(host) :
		inet_addr("127.0.0.1");
	size = sizeof(addr_server);
	if (connect(socket_a, (struct sockaddr *) &addr_server, size) ==
			-1)
		print_error("connection failed");
	printf("Connected to %s:%d\n", host, port);
	close(socket_a);
	return (0);
}
