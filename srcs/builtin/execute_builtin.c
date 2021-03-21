#include "minishell.h"

void	execute_builtin(t_command *cmd)
{
	int			ret;
	const void	(*builtinfunc[7])(t_command*) = {
		execute_echo(),
		execute_cd(),
		execute_pwd(),
		execute_export(),
		execute_unset(),
		execute_env(),
		execute_exit()
	};

	ret = is_builtin(cmd);
	builtinfunc[ret](cmd);
	return ;
}
