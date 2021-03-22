#include "minishell.h"

static t_command	*get_command(char **strs)
{
	int			i;
	t_command	*cmd;

	if (!strs)
		return (NULL);
	if ((cmd = create_new_tcommand()) == NULL)
		return (NULL);
	i = 0;
	while (strs[i] != NULL)
	{
		if (ft_strchr(strs[i], '<') || ft_strchr(strs[i], '>'))
		{
			if (!set_redirection_list(cmd, strs + i))
				return (wrap_free_commands_list(cmd));
			if (ft_strchr(strs[i + 1], '<') || ft_strchr(strs[i + 1], '>'))
				i++;
			i += 2;
		}
		else
		{
			if ((cmd->argv = add_str_to_list(cmd->argv, strs[i++])) == NULL)
				return (wrap_free_commands_list(cmd));
		}
	}
	return (cmd);
}

static t_command	*get_pipeline(char **strs)
{
	int			i;
	t_command	*pipeline;

	if (!strs)
		return (NULL);
	if ((i = strschr(strs, "|")) < 0)
		return (get_command(strs));
	if ((pipeline = get_pipeline(get_strs(strs, i))) == NULL)
		return (NULL);
	pipeline->op = PIPELINE;
	if ((pipeline->next = get_pipeline(get_strs(strs + i + 1, 0))) == NULL)
		return (wrap_free_commands_list(pipeline));
	pipeline->next->receive_pipe = true;
	return (pipeline);
}

static t_command	*get_andor(char **strs)
{
	int			i;
	t_command	*andor;

	if (!strs)
		return (NULL);
	if ((i = strschr(strs, "&|")) < 0 || (!ft_strchr(strs[i + 1], '&') && \
	!ft_strchr(strs[i + 1], '|')))
		return (get_pipeline(strs));
	if ((andor = get_andor(get_strs(strs, i))) == NULL)
		return (NULL);
	/*if (ft_strchr(strs[i + 1], '&'))
	**	andor.? = AND;
	**else
	**	andor.? = PIPELINE;
	*/
	if ((andor->next = get_andor(get_strs(strs + i + 1, 0))) == NULL)
		return (wrap_free_commands_list(andor));
	return (andor);
}

static t_command	*get_list(char **strs)
{
	int			i;
	t_command	*list;

	if (!strs)
		return (NULL);
	if ((i = strschr(strs, ";&")) < 0)
		return (get_andor(strs));
	if ((list = get_list(get_strs(strs, i))) == NULL)
		return (NULL);
	if (ft_strchr(strs[i], ';'))
		list->op = SCOLON;
	/*else
	**	list->op = AND;
	*/
	if ((list->next = get_list(get_strs(strs + i + 1, 0))) == NULL)
		return (wrap_free_commands_list(list));
	return (list);
}

t_command			*get_commandline(char **strs)
{
	t_command	*cmds;
	t_command	*head;
	char		*last;

	if (!strs)
		return (NULL);
	last = get_laststr(strs);
	if (ft_strchr(last, ';') || ft_strchr(last, '&'))
		cmds = get_list(get_strs(strs, -1));
	else
		cmds = get_list(strs);
	head = cmds;
	while (cmds->next)
		cmds = cmds->next;
	if (ft_strchr(last, ';'))
		cmds->op = SCOLON;
	/*if (ft_strchr(last, '&'))
	**	cmds->op = AND;
	*/
	return (head);
}
