#include "minishell.h"

int main(void)
{
	t_command *cmd;

	create_newenv();
	add_newval_to_env("arg");
	add_newval_to_env("test=1");
	cmd = create_new_tcommand();
	cmd->argv = ft_split("env,arg",',');
	execute_env(cmd);
	free_commandslist(&cmd);
}
