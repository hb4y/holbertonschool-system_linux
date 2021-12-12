#include "server_aux.h"

/**
 * get_req - get req
 * @req: request
 * Return: code
 */
int get_req(char *req)
{
	char *route = NULL, c_eol[] = " \xD\xA", *pl = NULL, *c_r = NULL;
	char *q = NULL, *keep = NULL, *key = NULL, *value = NULL;

	strtok(req, c_eol);
	c_r = strtok(NULL, c_eol);
	route = strtok(c_r, "?");
	printf("Path: %s\n", route);
	q = strtok(NULL, "?");
	keep = q;
	pl = strtok_r(q, "&", &keep);
	while (pl)
	{
		key = strtok(pl, "=");
		value = strtok(NULL, "=");
		printf("Query: \"%s\" -> \"%s\"\n", key, value);
		pl = strtok_r(NULL, "&", &keep);
	}

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
