#include "minishell.h"

static bool	has_tilde(char *line)
{
	if (!line)
		return (true);
	if (line[0] == '~' && (line[1] == '\0' || line[1] == '/'))
		return (true);
	return (false);
}

char	*expand_firsttilde(char *arg)
{
	char	*home;

	if (!has_tilde(arg))
		return (ft_strdup(arg));
	home = getenv("HOME");
	if (!arg)
		return (ft_strdup(home));
	return (ft_strjoin(home, arg + 1));
}
