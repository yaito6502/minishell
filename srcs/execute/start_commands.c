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
				store_exitstatus(SAVE, ret);
			}
		}
		else
			store_exitstatus(SAVE, cmd_ptr->exitstatus);
		cmd_ptr = cmd_ptr->next;
	}
	return ;
}

void		start_commands(t_command *cmd)
{
	t_command	*cmd_ptr;

	if (!preprocess_command(cmd))
		return ;
	reconnect_stdfd(SAVE);
	cmd_ptr = cmd;
	while (cmd != NULL)
	{
		if (cmd->op == PIPELINE || cmd->receive_pipe == true)
			cmd->exitstatus = execute_parallel(cmd);
		else
		{
			cmd->exitstatus = execute_sequential(cmd);
			reconnect_stdfd(LOAD);
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
