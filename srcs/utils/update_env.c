#include "minishell.h"

/*
**元々、execute_cdの中の関数で無理やり一つにまとめていたので可読性が低いです。
** key = value　の形で環境変数を更新する。
*/

bool	update_env(char *key, char *value)
{
	extern char	**environ;
	char		*env;
	char		*tmp;
	bool		status;
	size_t		i;

	if (!validate_envkey(key))
		return (false);
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (false);
	env = ft_strjoin(tmp, value);
	free(tmp);
	if (!env)
		return (false);
	i = 0;
	while (environ[i] != NULL && ft_strncmp(environ[i], key, ft_strlen(key)))
		i++;
	status = (environ[i] == NULL ? add_newval_to_env(env) : true);
	(environ[i] == NULL ? free(env) : free(environ[i]));
	if (environ[i] != NULL)
		environ[i] = env;
	return (status);
}
