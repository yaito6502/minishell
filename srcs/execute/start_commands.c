#include "minishell.h"

static void	confirm_child(t_command *cmd_ptr, t_command *cmd)
{
	int			status;
	int			ret;
	t_command	*end;

	if (cmd->next == NULL)
		end = NULL;
	end = cmd->next;
	while (cmd_ptr != end)
	{
		if (cmd_ptr->has_childproc == true)
		{
			ret = waitpid(cmd_ptr->pid, &status, 0);
			if (WIFEXITED(status))
			{
				ret = WEXITSTATUS(status);
				store_exitstatus(0, ret);
			}
		}
		else
			store_exitstatus(0, cmd_ptr->exitstatus);
		printf("%d\n", store_exitstatus(1, 0));//for debug
		cmd_ptr = cmd_ptr->next;
	}
	return ;
}

void		start_commands(t_command *cmd)
{
	t_command	*cmd_ptr;

	reconnect_stdfd(0);
	cmd_ptr = cmd;
	while (cmd != NULL)
	{
		if (cmd->op == PIPELINE || cmd->receive_pipe == true)
			execute_parallel(cmd);
		else
		{
			execute_sequential(cmd);
			reconnect_stdfd(1);
		}
		if (cmd->op == SCOLON || cmd->op == EOS)
		{
			confirm_child(cmd_ptr, cmd);
			cmd_ptr = cmd->next;
		}
		cmd = cmd->next;
	}
	free_commandslist(&cmd);
	return ;
}
