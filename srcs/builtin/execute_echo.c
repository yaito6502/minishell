#include "minishell.h"

/*
** ビルトインコマンドechoを再現した関数。
** 引数に与えられた文字列を順番にスペースを挟んで出力する。
** ""など空の文字列があった場合もスペースを挟む。
*/

/*
** nオプションの有無をflagに格納、出力を始めるindexを返す。
** 最初の引数から任意の数-nが続く→有効、-nnnnnnnnn…→有効。
** -n[n以外の文字]→無効、そのまま出力
** 無効なオプションを見つけた時点でそのインデックスを返す。
*/

static int	get_option(char **argv, bool *flag)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i] != NULL)
	{
		j = 0;
		if (argv[i][j] != '-')
			break ;
		j++;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] != 'n')
				return (i);
			j++;
		}
		*flag = true;
		i++;
	}
	return (i);
}

void		execute_echo(t_command *cmd)
{
	bool	op_flag;
	int		i;

	op_flag = false;
	i = get_option(cmd->argv, &op_flag);
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
