#include "minishell.h"

static bool	error_piping(void)
{
	ft_putstr_fd("minishell: pipe: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	return (false);
}

bool		send_pipeline(t_command *cmd, int newpipe[2])
{
	if (cmd->op != PIPELINE)
		return ;
	if (close(newpipe[0]) == -1)
		return (error_piping());
	if (dup2(newpipe[1], STDOUT_FILENO) == -1)
		return (error_piping());
	if (close(newpipe[1]) == -1)
		return (error_piping());
	return (true);
}

bool		receive_pipeline(t_command *cmd)
{
	int	ret;

	if (cmd->receive_pipe == false)
		return ;
	if (close(cmd->lastfd[1]) == -1)
		return (error_piping());
	if (dup2(cmd->lastfd[0], STDIN_FILENO) == -1)
		return (error_piping());
	if (close(cmd->lastfd[0]) == -1)
		return (error_piping());
	return (true);
}

/*
** dup2のエラーキャッチが必要かも。要検討
*/
