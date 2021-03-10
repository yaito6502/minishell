#include "minishell.h"

int		main(void)
{
	t_command *ptr;

	ptr = create_new_tcommand();
	ptr->argv = ft_split("echo,hello world", ',');
	ptr->redirect_in = ft_split("infile,infle2", ',');
	ptr->redirect_out = ft_split(">,test1,2>,test2", ',');
	ptr->next = create_new_tcommand();
	ptr->next->next = create_new_tcommand();

	free_commandslist(&ptr);
	return 0;

}