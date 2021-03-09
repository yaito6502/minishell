#include "minishell.h"

void	execute_builtin(t_command *cmds)
{
	//cmds->argv[0]を確認して、該当するbuiltinコマンド関数に振り分ける。
	int		ret;

	ret = is_builtin(cmds);
	if (ret == 0)

	if (ret == 1)
	if (ret == 2)
	if (ret == 3)
	if (ret == 4)
	if (ret == 5)
	if (ret == 6)

	return ;
}