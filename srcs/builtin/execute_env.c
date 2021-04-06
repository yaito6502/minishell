#include "minishell.h"

/*
** ビルトインコマンドenvを再現した関数。環境変数のkey,valueを出力する。ソートはしない。
*/

int	execute_env(t_command *cmd)
{
	extern char	**environ;
	int			i;

	(void)cmd;
	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strchr(environ[i], '='))
			printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}
