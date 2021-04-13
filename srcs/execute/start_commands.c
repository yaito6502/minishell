#include "minishell.h"

static void	confirm_child(t_command *cmd_ptr, t_command *cmd)
{
	int			status;
	int			ret;
	t_command	*end;

	end = cmd->next;
	while (cmd_ptr != end)
	{
		if (cmd_ptr->has_childproc == true)
		{
			ret = waitpid(cmd_ptr->pid, &status, 0);
			if (WIFEXITED(status))
				store_exitstatus(SAVE, WEXITSTATUS(status));
			if (WIFSIGNALED(status) && WTERMSIG(status) == 3
				&& cmd_ptr->next == NULL)
			{
				if (WCOREDUMP(status))
					write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
				else
					write(STDOUT_FILENO, "Quit\n", 5);
			}
		}
		else
			store_exitstatus(SAVE, cmd_ptr->exitstatus);
		cmd_ptr = cmd_ptr->next;
	}
}

void	start_commands(t_command *cmd)
{
	t_command	*cmd_ptr;

	reconnect_stdfd(SAVE);
	cmd_ptr = cmd;
	while (cmd != NULL)
	{
		if (!preprocess_command(cmd))
			return ;
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
