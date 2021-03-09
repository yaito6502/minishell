#include "minishell.h"

static void	execute_child(t_command *cmds)
{
	extern char **__environ;

	send_pipeline();
	receive_pipeline();
	redirect_input();
	redirect_output();
	if (!is_builtin())
		execve(cmds->argv[0], cmds->argv, __environ);
	execute_builtin(cmds);
	exit(EXIT_SUCCESS);
}

void	execute_parallel(t_command *cmds)
{
	int			status;
	int			newpipe[2];
	pid_t		pid;

	if (cmds->op == PIPELINE)
		pipe(newpipe);
	pid = fork();
	if (pid == 0)
		execute_child(cmds);
	if (cmds->receive_pipe == true)
	{
		close(cmds->lastfd[0]);
		close(cmds->lastfd[1]);
	}
	cmds->pid = pid;
	cmds->next->receive_pipe = true;
	cmds->next->lastfd[0] = newpipe[0];
	cmds->next->lastfd[1] = newpipe[1];
	return ;
}