#include "minishell.h"

int main(void)
{
	t_command *cmd;

	cmd = create_new_tcommand();
	cmd->argv = ft_split("env,arg",',');
	execute_env(cmd);
	free_commandslist(&cmd);
}