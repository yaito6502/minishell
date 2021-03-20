#include "minishell.h"

/*
** environに新しいメンバを追加。追加する文字列は関数内でmallocする。
** mallocに失敗したときfalseを返す。
*/

bool	add_newval_to_env(const char *str)
{
	int			i;
	char		*new_value;
	char		**new_env;
	extern char	**environ;

	if (!(new_value = ft_strdup(str)))
		return (false);
	i = 0;
	while (environ[i] != NULL)
		i++;
	new_env = (char **)ft_sprealloc(environ, (i + 2) * sizeof(char *));
	if (new_env == NULL)
		return (false);
	environ = new_env;
	environ[i] = new_value;
	environ[i + 1] = NULL;
	return (true);
}
