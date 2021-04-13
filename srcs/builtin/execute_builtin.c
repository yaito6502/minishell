#include "minishell.h"

int	execute_builtin(t_command *cmd)
{
	int	ret;
	int	(*builtinfunc[7])(t_command*);

	builtinfunc[0] = execute_echo;
	builtinfunc[1] = execute_cd;
	builtinfunc[2] = execute_pwd;
	builtinfunc[3] = execute_export;
	builtinfunc[4] = execute_unset;
	builtinfunc[5] = execute_env;
	builtinfunc[6] = execute_exit;
	ret = is_builtin(cmd);
	return (builtinfunc[ret](cmd));
}
