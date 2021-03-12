#include "minishell.h"

void		send_pipeline(t_command *cmds, int newpipe[2])
{
	if (cmds->op != PIPELINE)
		return ;
	close(newpipe[0]);
	dup2(newpipe[1], STDOUT_FILENO);
	close(newpipe[1]);
	return ;
}

void		receive_pipeline(t_command *cmds)
{
	if (cmds->receive_pipe == false)
		return ;
	close(cmds->lastfd[1]);
	dup2(cmds->lastfd[0], STDIN_FILENO);
	close(cmds->lastfd[0]);
	return ;
}

/*
** dup2のエラーキャッチが必要かも。要検討
*/
