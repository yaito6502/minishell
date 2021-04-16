#include "minishell.h"

t_command	*get_lastcommand(t_command *cmds)
{
	t_command	*head;

	head = cmds;
	while (head->next)
		head = head->next;
	return (head);
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

int	strsncmp(char **strs, char *set)
{
	size_t	i;

	if (!strs || !set)
		return (-1);
	i = 0;
	while (strs[i] != NULL)
	{
		if (!ft_strncmp(strs[i], set, 2))
			return (i);
		i++;
	}
	return (-1);
}

bool	endswith(char *str, char *end)
{
	char	elen;

	elen = ft_strlen(end);
	return (!ft_strncmp(str + (ft_strlen(str) - elen), end, elen + 1));
}
