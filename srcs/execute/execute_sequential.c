#include "minishell.h"

static void	sequential_chlidproc(t_command *cmd)
{
	extern char	**environ;
	char		*cmdpath;

	if (has_slash(cmd->argv[0]))
		execve(cmd->argv[0], cmd->argv, environ);
	else
	{
		cmdpath = get_cmd_frompath(cmd);
		if (cmdpath != NULL)
			execve(cmdpath, cmd->argv, environ);
		else
			wrap_exit(error_execute(cmd->argv[0], EFAULT));
		wrap_exit(error_execute(cmdpath, errno));
	}
	wrap_exit(error_execute(cmd->argv[0], errno));
}

int	execute_sequential(t_command *cmd)
{
	if (!do_redirection(cmd))
		return (1);
	if (!cmd->argv || !cmd->argv[0])
		return (0);
	if (is_builtin(cmd) != -1)
		return (execute_builtin(cmd));
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (error_fork());
	cmd->has_childproc = true;
	if (cmd->pid == 0)
		sequential_chlidproc(cmd);
	return (0);
}
