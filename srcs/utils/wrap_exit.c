#include "minishell.h"

void	wrap_exit(unsigned int status)
{
	extern char			**environ;
	extern t_termcap	term;

	ft_free_split(environ);
	free_tterm(term);
	exit(status);
}
