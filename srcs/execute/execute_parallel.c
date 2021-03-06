#include "minishell.h"

static int	error_pipe(void)
{
	ft_putstr_fd("minishell: pipe: ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	return (1);
}

static void	preprocess_parallel(t_command *cmd, int newpipe[2])
{
	if (!connect_pipeline(cmd, newpipe))
		wrap_exit(EXIT_FAILURE);
	if (!do_redirection(cmd))
		wrap_exit(EXIT_FAILURE);
	if (!cmd->argv || !cmd->argv[0])
		wrap_exit(EXIT_SUCCESS);
	if (is_builtin(cmd) != -1)
		wrap_exit(execute_builtin(cmd));
}

static void	parallel_childproc(t_command *cmd, int newpipe[2])
{
	extern char	**environ;
	char		*path;

	preprocess_parallel(cmd, newpipe);
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

int	execute_parallel(t_command *cmd)
{
	int	newpipe[2];

	if (cmd->op == PIPELINE)
		if (pipe(newpipe) == -1)
			return (error_pipe());
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (error_fork());
	cmd->has_childproc = true;
	if (cmd->pid == 0)
		parallel_childproc(cmd, newpipe);
	if (cmd->receive_pipe == true)
	{
		close(cmd->lastfd[0]);
		close(cmd->lastfd[1]);
	}
	if (cmd->op == PIPELINE)
	{
		cmd->next->lastfd[0] = newpipe[0];
		cmd->next->lastfd[1] = newpipe[1];
	}
	return (0);
}
