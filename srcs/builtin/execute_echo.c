#include "minishell.h"

/*
** ビルトインコマンドechoを再現した関数。
** 引数に与えられた文字列を順番にスペースを挟んで出力する。
** ""など空の文字列があった場合もスペースを挟む。
*/

void	execute_echo(t_command *cmd)
{
	int	i;

	i = 1;
	while (cmd->argv[i] != NULL)
	{
		printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1] != NULL)
			printf(" ");
		i++;
	}
	printf("\n");
	return ;
}
