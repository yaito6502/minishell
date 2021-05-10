#include "minishell.h"

static void	sequential_chlidproc(t_command *cmd)
{
	extern char	**environ;
	char		*path;

	path = getenv("PATH");
	if (has_slash(cmd->argv[0]) || path == NULL || path[0] == '\0')
	{
		if (is_dir(cmd->argv[0]))
			wrap_exit(error_execute(cmd->argv[0], EISDIR));
		execve(cmd->argv[0], cmd->argv, environ);
	}
	else
	{
		path = get_cmd_frompath(cmd);
		if (path == NULL)
			wrap_exit(error_execute(cmd->argv[0], EFAULT));
		execve(path, cmd->argv, environ);
		wrap_exit(error_execute(path, errno));
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
