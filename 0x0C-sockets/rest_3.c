#include "server_aux.h"

/**
 * get_req - get req
 * @req: request
 * Return: code
 */
int get_req(char *req)
{
	char *route = NULL, *value = NULL, *key = NULL;
	char *keep = NULL, *body = NULL;
	char *p = NULL, *s_p = NULL;
	char c_eol[] = "\xD\xA", s_break[] = "\xD\xA\xD\xA";
	char *l = NULL;
	int i = 0;

	keep = req;
	l = strtok_r(req, c_eol, &keep);
	strtok(l, " ");
	route = strtok(NULL, " ");
	printf("Path: %s\n", route);
	for (i = 0; keep && keep[i] != '\0'; i++)
	{
		if (keep[i] == '\xD' && !strncmp(&keep[i], s_break, 4))
		{
			break;
		}
	}
	if (!keep || keep[i] == '\0')
		return (400);
	req = &keep[i];
	keep = req;
	body = strtok_r(req, c_eol, &keep);
	while (body)
	{
		s_p = body;
		p = strtok_r(body, "&", &s_p);
		while (p)
		{
			key = strtok(p, "=");
			value = strtok(NULL, "=");
			printf("Body param: \"%s\" -> \"%s\"\n", key, value);
			p = strtok_r(NULL, "&", &s_p);
		}
		body = strtok_r(NULL, c_eol, &keep);
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
