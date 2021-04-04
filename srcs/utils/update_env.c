#include "minishell.h"

/*
**元々、execute_cdの中の関数で無理やり一つにまとめていたので可読性が低いです。
** key = value　の形で環境変数を更新する。
*/

static char	*generate_keyvalue(char *key, char *value)
{
	char	*tmp;
	char	*env;

	if (!validate_envkey(key))
		return (NULL);
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	env = ft_strjoin(tmp, value);
	free(tmp);
	return (env);
}

bool		update_env(char *key, char *value)
{
	extern char	**environ;
	char		*env;
	bool		status;
	size_t		i;

	env = generate_keyvalue(key, value);
	if (!env)
		return (false);
	i = 0;
	while (environ[i] != NULL && ft_strncmp(environ[i], key, ft_strlen(key)))
		i++;
	if (environ[i] == NULL)
	{
		status = add_newval_to_env(env);
		free(env);
		return (status);
	}
	free(environ[i]);
	environ[i] = env;
	return (true);
}
