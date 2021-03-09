#include "minishell.h"

static void	free_command(t_command *cmds)
{
	ft_free_split(cmds->argv);
	ft_free_split(cmds->redirect_in);
	ft_free_split(cmds->redirect_out);
	free(cmds);
}

void		free_commandslist(t_command **cmds)
{
	t_command *lst_ptr;

	lst_ptr = *cmds;
	while (*cmds)
	{
		lst_ptr = (*cmds)->next;
		free_command(*cmds);
		*cmds = lst_ptr;
	}
	*cmds = NULL;
}