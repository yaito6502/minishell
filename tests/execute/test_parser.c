#include "minishell.h"

int		main(void)
{
	t_command *cmds;

	cmds = get_commandline("echo hello > file1 > file2 ; cat < file2 | head -n 1 | wc");
	while (cmds)
	{
		print_tcommand(*cmds);
		cmds = cmds->next;
	}
	return (0);
}
