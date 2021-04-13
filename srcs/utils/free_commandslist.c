#include "minishell.h"

static void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	ft_free_split(cmd->argv);
	ft_free_split(cmd->redirect_in);
	ft_free_split(cmd->redirect_out);
	free(cmd);
}

void	*free_commandslist(t_command **cmds)
{
	t_command	*lst_ptr;

	if (!cmds || !*cmds)
		return (NULL);
	lst_ptr = *cmds;
	while (*cmds)
	{
		lst_ptr = (*cmds)->next;
		free_command(*cmds);
		*cmds = lst_ptr;
	}
	cmds = NULL;
	return (NULL);
}
