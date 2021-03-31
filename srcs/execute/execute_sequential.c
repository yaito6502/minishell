#include "minishell.h"

static void	sequential_chlidproc(t_command *cmd)
{
	extern char	**environ;
	int			ret;

	if (has_slash(cmd->argv[0]))
		execve(cmd->argv[0], cmd->argv, environ);
	else
		execve(get_cmd_frompath(cmd), cmd->argv, environ);
	ret = error_execute(cmd->argv[0]);
	exit(ret);
}

int			execute_sequential(t_command *cmd)
{
	if (!do_redirection(cmd))
		return (1);
	if (is_builtin(cmd) != -1)
		return (execute_builtin(cmd));
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (1);//return (error_execute());
	cmd->has_childproc = true;
	if (cmd->pid == 0)
		sequential_chlidproc(cmd);
	return (0);
}
