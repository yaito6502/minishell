#include "minishell.h"

static void	print_signal_message(t_command *cmd, int status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == 3 && cmd->next == NULL)
	{
		if (WCOREDUMP(status))
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
		else
			write(STDOUT_FILENO, "Quit\n", 5);
	}
}

static t_command	*confirm_child(t_command *cmd_ptr, t_command *cmd)
{
	int			status;
	t_command	*end;

	end = cmd->next;
	while (cmd_ptr != end)
	{
		if (cmd_ptr->has_childproc == true)
		{
			if (waitpid(cmd_ptr->pid, &status, 0) == -1)
			{
				ft_putstr_fd("minishell: waitpid: ", STDERR_FILENO);
				ft_putendl_fd(strerror(errno), STDERR_FILENO);
			}
			if (WIFEXITED(status))
				store_exitstatus(SAVE, WEXITSTATUS(status));
			print_signal_message(cmd_ptr, status);
		}
		else
			store_exitstatus(SAVE, cmd_ptr->exitstatus);
		cmd_ptr = cmd_ptr->next;
	}
	return (end);
}

void	start_commands(t_command *cmd)
{
	t_command	*cmd_ptr;

	reconnect_stdfd(SAVE);
	cmd_ptr = cmd;
	while (cmd != NULL)
	{
		if (!validate_redirect(cmd))
		{
			cmd = cmd->next;
			continue ;
		}
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
			cmd_ptr = confirm_child(cmd_ptr, cmd);
		cmd = cmd->next;
	}
}
