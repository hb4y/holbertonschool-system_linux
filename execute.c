#include "ls.h"

/**
 * execute - execute the listing of the dirs.
 * Description: execute.
 * @options: options for the output detail.
 * @to_read: dirs to read.
 * Return: void
 **/
void execute(char *options, char **to_read)
{
	DIR *current;
	struct dirent *directory;

	if (options == NULL && to_read == NULL)
	{
		current = opendir(".");

		if (current)
		{
			while ((directory = readdir(current)) != NULL)
			{
				if ((directory->d_name)[0] != '.')
					printf("%s ", directory->d_name);
			}
			printf("\n");
			closedir(current);
		}
	}
}
