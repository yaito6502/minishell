#include "minishell.h"

int main(void)
{
	t_command	*cmd;
	t_command	*next;

	cmd = create_new_tcommand();
	cmd->argv = ft_split("echo,hello world.\n",',');
	cmd->redirect_out = ft_split(">,testinout/outfile",',');
	cmd->op = PIPELINE;
	cmd->next = create_new_tcommand();
	next = cmd->next;
	next->argv = ft_split("ls,./srcs/execute",',');
	next->op = PIPELINE;
	cmd->next->next = create_new_tcommand();
	next = cmd->next->next;
	next->argv = ft_split("grep,do",',');
	next->op = SCOLON;
	cmd->next->next->next = create_new_tcommand();
	next = next->next;
	next->argv = ft_split("cat,tests/execute/test_join_path.c",',');
	next->op = EOS;


	start_commands(cmd);
	free_commandslist(&cmd);
	return 0;
}