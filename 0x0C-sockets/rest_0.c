#include "server_aux.h"

/**
 * get_req - get req
 * @req: request
 * Return: code
 */
int get_req(char *req)
{
	char *met = NULL, *route = NULL, *ver = NULL, c_eol[] = " \xD\xA";

	met = strtok(req, c_eol);
	route = strtok(NULL, c_eol);
	ver = strtok(NULL, c_eol);
	printf("Method: %s\nPath: %s\nVersion: %s\n", met, route, ver);
	return (200);
}

/**
 * respon - handle the client response
 * @socket_client: fd
 * @status: status
 */
void respon(int socket_client, int status)
{
	int size = 0;
	char res[8192] = {0};

	switch (status)
	{
		case 200:
			sprintf(res, "HTTP/1.1 200 OK%s%s", "\xD\xA", "\xD\xA");
			break;
	}
	size = strlen(res);
	if (send(socket_client, res, size, 0) != size)
		print_error("send res failed");
}
