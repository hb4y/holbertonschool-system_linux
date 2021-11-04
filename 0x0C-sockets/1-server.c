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
 * main - listens to traffic on port 12345
 * Return: 0 or error
 */
int main(void)
{
	int socket_a = 0, socket_c = 0;
	int size = 0, c_size = 0;
	struct sockaddr_in addr_server, addr_client;

	socket_a = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socket_a == -1)
		print_error("socket failed");
	addr_server.sin_family = AF_INET;
	addr_server.sin_port = htons(12345);
	addr_server.sin_addr.s_addr = htonl(INADDR_ANY);
	size = sizeof(addr_server);
	if (bind(socket_a, (struct sockaddr *) &addr_server, size) == -1)
		print_error("bind failed");
	if (listen(socket_a, 10) == -1)
		print_error("listen failed");
	printf("Socket server listen on port %d\n", 12345);
	c_size = sizeof(addr_client);
	socket_c = accept(socket_a, (struct sockaddr *) &addr_client, (
				(socklen_t *) &c_size));
	if (socket_c == -1)
		print_error("accept failed");
	printf("Client connected: %s\n", inet_ntoa(addr_client.sin_addr));
	close(socket_c);
	close(socket_a);
	return (0);
}
