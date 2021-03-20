#include "minishell.h"

static void	confirm_child(t_command *cmd_ptr, t_command *cmd)
{
	int	status;
	int	ret;
	t_command *end;

	end = cmd->next;
	while (cmd_ptr != end)
	{
		ret = waitpid(cmd_ptr->pid, &status, 0);
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

int main(void)
{
	t_command	*cmd;
	t_command	*cmd_ptr;

	cmd = create_new_tcommand();
	cmd->argv = ft_split("echo,hello world.\n",',');
	cmd->redirect_out = ft_split(">,testinout/outfile",',');
	cmd->op = PIPELINE;
	cmd->next = create_new_tcommand();
	cmd->next->argv = ft_split("ls,./srcs/execute",',');
	cmd->next->op = PIPELINE;
	cmd->next->next = create_new_tcommand();
	cmd->next->next->argv = ft_split("grep,do",',');
	cmd->next->next->op = EOS;

	cmd_ptr = cmd;
	while (cmd != NULL)
	{
		if (cmd->op == PIPELINE || cmd->receive_pipe == true)
			execute_parallel(cmd);
		if (cmd->op == SCOLON || cmd->op == EOS)
			confirm_child(cmd_ptr, cmd);
		cmd = cmd->next;
	}
	free_commandslist(&cmd_ptr);
	return 0;
}
