#include "minishell.h"

t_command	*get_lastcommand(t_command *cmds)
{
	t_command *head;

	head = cmds;
	while (head->next)
		head = head->next;
	return (head);
}

char		**get_strs(char **list, int len)
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

int			strsncmp(char **strs, char *set)
{
	size_t i;
	size_t j;

	if (!strs || !set)
		return (-1);
	i = 0;
	while (strs[i] != NULL)
	{
		j = 0;
		if (!ft_strncmp(strs[i], set, 2))
			return (i);
		i++;
	}
	return (-1);
}

void		*wrap_free_commands_list(t_command *cmds)
{
	free_commandslist(&cmds);
	return (NULL);
}

void		*wrap_ft_free_split(char **strs)
{
	ft_free_split(strs);
	return (NULL);
}
