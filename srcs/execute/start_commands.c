#include "minishell.h"

static void	confirm_child(t_command *cmd_ptr, t_command *cmds)
{
	int status;

	cmds = cmds->next;
	while (cmd_ptr != cmds)
	{
		waitpid(cmd_ptr->pid, &status, 0);
		cmd_ptr = cmd_ptr->next;
	}
	return ;
}

static void	copy_stdinout(int fd[3])
{
	fd[0] = dup(0);
	fd[1] = dup(1);
	fd[2] = dup(2);
	return ;
}

void		start_commands(t_command *cmds)
{
	t_command	*cmd_ptr;
	int			default_fd[3];

	copy_stdinout(&default_fd);
	while (cmds != NULL)
	{
		cmd_ptr = cmds;
		if (cmds->op == PIPELINE || cmds->receive_pipe == true)
			execute_parallel(cmds);
		else
		{
			execute_sequential(cmds);
			reconnect_std(default_fd);
		}
		if (cmds->op == SCOLON || cmds->op == EOS)
			confirm_child(cmd_ptr, cmds);
		cmds = cmds->next;
	}
	free_commandslist(&cmds);
	return ;
}
