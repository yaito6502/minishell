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
		ret = waitpid(cmd_ptr->pid, &status, 0);
		//出力はデバッグ用、コマンドに合わせて終了ステータスを設定
		if (ret == -1)
		{
			puts("something wrong!");
		}
		if (WIFEXITED(status))
			printf("child process ended successfully.\n");
		else
			printf("something wrong.\n");
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
	return ;//call read_command func
}
