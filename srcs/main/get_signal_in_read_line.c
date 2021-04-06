#include "minishell.h"

#define BUFFER_SIZE	2048

char	*get_eof(char *line, char *c, int i)
{
	if (i != 0)
	{
		write(STDOUT_FILENO, "\007", 1);
		return (line);
	}
	ft_strlcpy(line, "exit", BUFFER_SIZE);
	write(STDOUT_FILENO, line, 4);
	ft_strlcpy(c, "\n", 8);
	return (line);
}

char	*get_sigint(char *line, char *c)
{
	line[0] = '\0';
	ft_strlcpy(c, "\n", 8);
	return (line);
}
