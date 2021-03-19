#include "minishell.h"

int		main(void)
{
	t_command	*cmd;
	char		*list1[19] = {"echo", "hello", ">", "file1", ">", "file2", "world", ";", "cat", "<", "file2", "|", "head", "-n", "1", "|", "wc", ";", NULL};
	char		*list2[3] = {"echo", "hello", NULL};

	if ((cmd = get_commandline(list1)) != NULL)
		print_tcommand(*cmd);
	free_commandslist(&cmd);
	if ((cmd = get_commandline(list2)) != NULL)
		print_tcommand(*cmd);
	free_commandslist(&cmd);
	return (0);
}
