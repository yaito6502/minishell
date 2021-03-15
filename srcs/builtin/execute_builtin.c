#include "minishell.h"

void	execute_builtin(t_command *cmd)
{
	int		ret;

	ret = is_builtin(cmd);
	if (ret == 0)
		execute_echo(cmd);
	else if (ret == 1)
		execute_cd(cmd);
	else if (ret == 2)
		execute_pwd(cmd);
	else if (ret == 3)
		execute_export(cmd);
	else if (ret == 4)
		execute_unset(cmd);
	else if (ret == 5)
		execute_env(cmd);
	else if (ret == 6)
		execute_exit(cmd);
	return ;
}