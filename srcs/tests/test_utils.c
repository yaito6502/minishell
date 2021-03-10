#include "minishell.h"

void	test_create_tcommand(void)
{
	t_command *ptr;

	ptr = create_new_tcommand();
	ptr->next = create_new_tcommand();
	ptr->argv = ft_split("echo,hello world", ',');
	ptr->redirect_in = ft_split("infile,infle2", ',');
	ptr->redirect_out = ft_split(">,test1,2>,test2", ',');
	print_tcommand(*ptr);
	return ;
}

int	main(void)
{
	test_create_tcommand();

	return (0);
}