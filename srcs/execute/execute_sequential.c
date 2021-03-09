#include "minishell.h"

static void	reconnect_std(int fd[3])
{
	dup2(0, fd[0]);
	dup2(1, fd[1]);
	dup2(2, fd[2]);
}

void		execute_sequential(t_command *cmds)
{
	pid_t	pid;
	extern	char **__environ;//仮

	redirect_input(cmds);
	redirect_output(cmds);
	if (is_builtin(cmds) != -1)
	{
		execute_builtin(cmds);
		return ;
	}
	if ((pid = fork()) == -1)
		;//error
	if (pid = 0)
		execve(cmds->argv[0], cmds->argv, __environ);
	else
	{
		cmds->pid = pid;
		return ;
	}
}
