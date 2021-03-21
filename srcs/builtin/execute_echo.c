#include "minishell.h"

/*
** ビルトインコマンドechoを再現した関数。
** 引数に与えられた文字列を順番にスペースを挟んで出力する。
** ""など空の文字列があった場合もスペースを挟む。
*/

void	execute_echo(t_command *cmd)
{
	bool	op_flag;
	int		i;

	op_flag = false;
	i = 1;
	if (!ft_strncmp("-n", cmd->argv[1], 3))
	{
		op_flag = true;
		i = 2;
	}
	while (cmd->argv[i] != NULL)
	{
		printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (op_flag == false)
		printf("\n");
	return ;
}
