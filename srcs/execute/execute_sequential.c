#include "minishell.h"

//エラー時、bool型等を返して判定する？

void	execute_sequential(t_command *cmd)
{
	extern char	**environ;

	redirect_input(cmd);
	redirect_output(cmd);
	if (is_builtin(cmd) != -1)
	{
		execute_builtin(cmd);
		return ;
	}
	cmd->pid = fork();
	//if (cmd->pid == -1)
	//	;//error
	if (cmd->pid == 0)
	{
		if (has_slash(cmd->argv[0]))
			execve(cmd->argv[0], cmd->argv, environ);
		execve(get_cmd_frompath(cmd), cmd->argv, environ);
	}
	return ;
}
