#include "server_aux.h"

/**
 * get_req - get req
 * @req: request
 * Return: code
 */
int get_req(char *req)
{
	char *header = NULL, *k = NULL;
	char c_eol[] = "\xD\xA";
	char *keep = NULL, *v_h = NULL;
	char *extr = NULL, *c = NULL;
	char *value_aux = NULL;

	keep = req;
	strtok_r(req, c_eol, &keep);
	header = strtok_r(NULL, c_eol, &keep);
	while (header)
	{
		k = strtok(header, ":");
		v_h = strtok(NULL, ":");
		extr = strtok(NULL, ":");
		value_aux = extr ? extr : "";
		c = extr ? ":" : "";
		printf("Header: \"%s\" -> \"%s%s%s\"\n", k, &v_h[1],
				c, value_aux);
		header = strtok_r(NULL, c_eol, &keep);
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
	int res_size = 0;
	char res[8192] = {0};

	switch (status)
	{
		case 200:
			sprintf(res, "HTTP/1.1 200 OK%s%s", "\xD\xA", "\xD\xA");
			break;
	}
	res_size = strlen(res);
	if (send(socket_client, res, res_size, 0) != res_size)
		print_error("send res failed");
}
