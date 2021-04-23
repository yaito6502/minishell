#include "minishell.h"

static bool	error_piping(char *str)
{
	ft_putstr_fd("minishell: connect_pipeline: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	return (false);
}

static bool	send_pipeline(t_command *cmd, int newpipe[2])
{
	if (cmd->op != PIPELINE)
		return (true);
	if (close(newpipe[0]) == -1)
		return (error_piping("close: "));
	if (dup2(newpipe[1], STDOUT_FILENO) == -1)
		return (error_piping("dup2: "));
	if (close(newpipe[1]) == -1)
		return (error_piping("close: "));
	return (true);
}

static bool	receive_pipeline(t_command *cmd)
{
	if (cmd->receive_pipe == false)
		return (true);
	if (close(cmd->lastfd[1]) == -1)
		return (error_piping("close: "));
	if (dup2(cmd->lastfd[0], STDIN_FILENO) == -1)
		return (error_piping("dup2: "));
	if (close(cmd->lastfd[0]) == -1)
		return (error_piping("close: "));
	return (true);
}

bool	connect_pipeline(t_command *cmd, int newpipe[2])
{
	if (!send_pipeline(cmd, newpipe))
		return (false);
	if (!receive_pipeline(cmd))
		return (false);
	return (true);
}
