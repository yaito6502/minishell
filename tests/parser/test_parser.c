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

void	print_strs(char **strs)
{
	size_t i = 0;
	while (strs[i] != NULL)
		printf("%s ", strs[i++]);
	puts("");
}

int		main(int argc, char **argv)
{
	t_command	*cmd;
	char		**token;
	(void)argc;

	token = tokenize(argv[1]);
	print_strs(token);
	if ((cmd = get_commandline(token)) != NULL)
		print_tcommand_iterate(cmd);
	free_commandslist(&cmd);
	ft_free_split(token);
	return (0);
}
