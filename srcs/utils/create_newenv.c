#include "minishell.h"

/*
** environをコピーした新しいenvを作成する。成功したらtrue、失敗したらfalseを返す。
** environが持つ各文字列もheap領域にコピーする。
*/

bool	create_newenv(void)
{
	extern char	**environ;
	char		**new_env;
	int			i;
	size_t		size;

	i = 0;
	while (environ[i] != NULL)
		i++;
	size = (i + 1) * sizeof(char *);
	if (!(new_env = (char **)malloc(size)))
		return (false);
	new_env[i] = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		new_env[i] = ft_strdup(environ[i]);
		i++;
	}
	environ = new_env;
	return (true);
}
