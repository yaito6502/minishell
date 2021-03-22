#include "minishell.h"

// ❯ ./test echo -nnnnnn hello world
// hello world%
// ❯ ./test echo  hello world
// hello world
// ❯ ./test echo  -ninvalid hello world
// -ninvalid hello world
// ❯ ./test echo  -n -n -n -n  hello world
// hello world%
// ❯ ./test echo  test -n -n -n -n  hello world
// test -n -n -n -n hello world

int main(int argc, char **argv)
{
	t_command *cmd;

	cmd = create_new_tcommand();
	cmd->argv = &argv[1];

	execute_echo(cmd);
	//free_commandslist(&cmd);
	return 0;
}