#include "minishell.h"

/*
** ビルトインコマンドenvを再現した関数。環境変数のkey,valueを出力する。ソートはしない。
*/

void	execute_env(t_command *cmd)
{
	extern char	**environ;
	int			i;

	(void)cmd;
	i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return ;
}
