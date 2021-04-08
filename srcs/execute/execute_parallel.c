#include "minishell.h"

static int	error_pipe(void)
{
	ft_putstr_fd("minishell: pipe: ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	return (1);
}

static void	parallel_childproc(t_command *cmd, int newpipe[2])
{
	extern char	**environ;

	if (!connect_pipeline(cmd, newpipe))
		exit(1);
	if (!do_redirection(cmd))
		exit(1);
	if (is_builtin(cmd) != -1)
		exit(execute_builtin(cmd));
	if (has_slash(cmd->argv[0]))
		execve(cmd->argv[0], cmd->argv, environ);
	else
		execve(get_cmd_frompath(cmd), cmd->argv, environ);
	exit(error_execute(cmd->argv[0]));
}

int			execute_parallel(t_command *cmd)
{
	int			newpipe[2];

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
