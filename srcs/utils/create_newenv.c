#include "minishell.h"

/*
** environをコピーした新しいenvを作成する。成功したらtrue、失敗したらfalseを返す。
** environが持つ各文字列もheap領域にコピーする。
*/

static bool	free_return(char **new_env, int failure_index)
{
	int	i;

	i = failure_index - 1;
	while (i >= 0)
	{
		free(new_env[i]);
		i--;
	}
	free(new_env);
	return (false);
}

bool	create_newenv(void)
{
	extern char	**environ;
	char		**new_env;
	int			i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	new_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (false);
	new_env[i] = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		new_env[i] = ft_strdup(environ[i]);
		if (new_env == NULL)
			return (free_return(new_env, i));
		i++;
	}
	environ = new_env;
	return (true);
}
