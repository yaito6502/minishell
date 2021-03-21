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
		len = i + len;
	}
	newlist = NULL;
	i = 0;
	while (list[i] != NULL && i < len)
		if ((newlist = add_str_to_list(newlist, list[i++])) == NULL)
			return (NULL);
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
		{
			if (ft_strchr(strs[i], set[j++]))
				return (i);
		}
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
	if (ft_strchr(*list, '<'))
	{
		if (!(cmd->redirect_in = add_str_to_list(cmd->redirect_in, list[0])))
			return (false);
		if (!(cmd->redirect_in = add_str_to_list(cmd->redirect_in, list[1])))
			return (false);
		/*if (ft_strchr(list[1], '<'))
		**	if (!(cmd->redirect_in = \
		**add_str_to_list(cmd->redirect_in, list[2])))
		**		return (false);
		*/
	}
	else if (ft_strchr(*list, '>'))
	{
		if (!(cmd->redirect_out = add_str_to_list(cmd->redirect_out, list[0])))
			return (false);
		if (!(cmd->redirect_out = add_str_to_list(cmd->redirect_out, list[1])))
			return (false);
		if (ft_strchr(list[1], '>'))
			if (!(cmd->redirect_out = \
			add_str_to_list(cmd->redirect_out, list[2])))
				return (false);
	}
	return (true);
}
