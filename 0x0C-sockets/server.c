#include "server_aux.h"

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
 * c_handler - client
 * @s_fd: file descriptor
 */
void c_handler(int s_fd)
{
	int s_c = 0, c_size = 0, r_size = 0, stat = 0;
	struct sockaddr_in addr_client;
	char req[8192] = {0};

	while (1)
	{
		c_size = sizeof(addr_client);
		s_c = accept(s_fd, (struct sockaddr *) &addr_client, (
					(socklen_t *) &c_size));
		if (s_c == -1)
			print_error("accept failed");
		printf("Client connected: %s\n", inet_ntoa(addr_client.sin_addr));
		req[0] = '\0';
		r_size = recv(s_c, req, 8192 - 1, 0);
		if (r_size == -1)
		{
			print_error("recieve failed");
		}
		else if (r_size > 0)
		{
			req[r_size] = '\0';
			printf("Raw request: \"%s\"\n", req);
			stat = get_req(req);
			respon(s_c, stat);
		}
		close(s_c);
	}
}

/**
 * main - main
 * Return: 0 on success
 */
int main(void)
{
	int s_fd = 0, server_size = 0;
	struct sockaddr_in addr_server;

	setbuf(stdout, NULL);
	s_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s_fd == -1)
		print_error("socket failed");
	addr_server.sin_family = AF_INET, addr_server.sin_port = htons(8080);
	addr_server.sin_addr.s_addr = htonl(INADDR_ANY);
	server_size = sizeof(addr_server);
	if (bind(s_fd, (struct sockaddr *) &addr_server, server_size) == -1)
		print_error("bind failed");
	if (listen(s_fd, 16) == -1)
		print_error("listen failed");
	printf("Server listening on port %d\n", 8080);
	c_handler(s_fd);
	close(s_fd);
	return (0);
}
