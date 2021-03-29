#include "minishell.h"

#define BUFFER_SIZE 1024
#define ERROR -1

char	*read_command(void)
{
	char	*buf;
	ssize_t	rdbyte;

	if ((buf = malloc(BUFFER_SIZE + 1)) == NULL)
		return (NULL);
	if ((rdbyte = read(STDIN_FILENO, buf, BUFFER_SIZE)) == ERROR)
	{
		free(buf);
		return (NULL);
	}
	if (rdbyte == 0)
	{
		free(buf);
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	buf[rdbyte - 1] = '\0';
	return (buf);
}
