#include "minishell.h"

static void	sequential_chlidproc(t_command *cmd)
{
	extern char	**environ;
	int			ret;

	if (has_slash(cmd->argv[0]))
		ret = execve(cmd->argv[0], cmd->argv, environ);
	else
		ret = execve(get_cmd_frompath(cmd), cmd->argv, environ);
	ret = error_execute(cmd->argv[0]);
	exit(ret);
}

void		execute_sequential(t_command *cmd)
{
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
	cmd->has_childproc = true;
	if (cmd->pid == 0)
		sequential_chlidproc(cmd);
	return ;
}
