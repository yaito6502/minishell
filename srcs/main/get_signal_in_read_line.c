#include "minishell.h"

void	get_eof(char *line, t_hist **hist)
{
	extern char			**environ;
	extern t_termcap	term;

	ft_free_split(environ);
	free(line);
	free_history(*hist);
	reset_terminal_setting();
	free_tterm(term);
	write(STDOUT_FILENO, "exit\n", 5);
	exit(EXIT_SUCCESS);
}

char	*get_sigint(char *line, char *c)
{
	line[0] = '\0';
	ft_strlcpy(c, "\n", 8);
	return (line);
}
