#include "minishell.h"

#define ERROR -1

char	*read_command(void)
{
	char	*buf;
	ssize_t	rdbyte;

	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	rdbyte = read(STDIN_FILENO, buf, BUFFER_SIZE);
	if (rdbyte == ERROR)
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
