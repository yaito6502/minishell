#include "minishell.h"

void	print_tcommand_iterate(t_command *cmds)
{
	t_command *head;

	head = cmds;
	while (head)
	{
		print_tcommand(*head);
		head = head->next;
		puts("");
	}
}

int		main(void)
{
	t_command	*cmd;
	char		*list1[19] = {"echo", "hello", ">", "file1", ">", "file2", "world", ";", "cat", "<", "file2", "|", "head", "-n", "1", "|", "wc", ";", NULL};
	char		*list2[3] = {"echo", "hello", NULL};

	puts("test1\n");
	if ((cmd = get_commandline(list1)) != NULL)
		print_tcommand_iterate(cmd);
	free_commandslist(&cmd);
	puts("\n\ntest2\n");
	if ((cmd = get_commandline(list2)) != NULL)
		print_tcommand_iterate(cmd);
	free_commandslist(&cmd);
	return (0);
}
