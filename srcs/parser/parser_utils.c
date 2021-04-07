#include "minishell.h"

char	*get_laststr(char **list)
{
	size_t i;

	if (!list)
		return (NULL);
	i = 0;
	while (list[i] != NULL)
		i++;
	return (list[i - 1]);
}

char	**get_strs(char **list, int len)
{
	char	**newlist;
	size_t	i;

	i = 0;
	if (len <= 0)
	{
		while (list[i] != NULL)
			i++;
		len += i;
	}
	newlist = NULL;
	i = 0;
	while (list[i] != NULL && i < (size_t)len)
	{
		newlist = add_str_to_list(newlist, list[i++]);
		if (newlist == NULL)
			break ;
	}
	return (newlist);
}

int		strschr(char **strs, char *set)
{
	size_t i;
	size_t j;

	if (!strs || !set)
		return (-1);
	i = 0;
	while (strs[i] != NULL)
	{
		j = 0;
		while (set[j])
			if (ft_strchr(strs[i], set[j++]))
				return (i);
		i++;
	}
	return (-1);
}

void	*wrap_free_commands_list(t_command *cmds)
{
	free_commandslist(&cmds);
	return (NULL);
}

bool	set_redirection_list(t_command *cmd, char **list)
{
	char	**target;

	if (ft_strchr(*list, '<'))
		target = cmd->redirect_in;
	else if (ft_strchr(*list, '>'))
		target = cmd->redirect_out;
	else
		return (false);
	target = add_str_to_list(target, list[0]);
	if (target == NULL)
		return (false);
	target = add_str_to_list(target, list[1]);
	if (target == NULL)
		return (false);
	if (ft_strchr(*list, '<'))
		cmd->redirect_in = target;
	else
		cmd->redirect_out = target;
	return (true);
}
