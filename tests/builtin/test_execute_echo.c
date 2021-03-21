#include "minishell.h"

int main(void)
{
	t_command *cmd;

	cmd = create_new_tcommand();
	cmd->argv = malloc(sizeof(char *) * 5);
	cmd->argv[0] = ft_strdup("echo");
	cmd->argv[1] = ft_strdup("hello");
	cmd->argv[2] = ft_strdup("");
	cmd->argv[3] = ft_strdup("world");
	cmd->argv[4] = NULL;

	execute_echo(cmd);
	free(cmd->argv[1]);
	cmd->argv[1] = ft_strdup("-n");
	execute_echo(cmd);
	free(cmd->argv[1]);
	cmd->argv[1] = ft_strdup("-ninvalid");
	execute_echo(cmd);
	free_commandslist(&cmd);
	return 0;
}