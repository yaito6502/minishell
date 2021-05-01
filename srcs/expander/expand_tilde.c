#include "minishell.h"

static bool	has_tilde(char *line)
{
	if (line[0] == '~' && (line[1] == '\0' || line[1] == '/'))
		return (true);
	return (false);
}

char	*expand_firsttilde(char *arg)
{
	if (!has_tilde(arg))
		return (ft_strdup(arg));
	return (ft_strjoin(getenv("HOME"), arg + 1));
}