#include "minishell.h"

static t_command	*get_command(char **strs)
{
	int			i;
	t_command	*cmd;

	if (!strs)
		return (NULL);
	cmd = create_new_tcommand();
	if (cmd == NULL)
		return (NULL);
	i = 0;
	while (strs[i] != NULL)
	{
		if (ft_strchr(strs[i], '<') || ft_strchr(strs[i], '>'))
		{
			if (!set_redirection_list(cmd, strs + i))
				return (wrap_free_commands_list(cmd));
			i += 2;
		}
		else
		{
			cmd->argv = add_str_to_list(cmd->argv, strs[i++]);
			if (cmd->argv == NULL)
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
	{
		pipeline = get_command(strs);
		ft_free_split(strs);
		return (pipeline);
	}
	pipeline = get_pipeline(get_strs(strs, i));
	if (pipeline == NULL)
	{
		ft_free_split(strs);
		return (NULL);
	}
	pipeline->op = PIPELINE;
	pipeline->next = get_pipeline(get_strs(strs + i + 1, 0));
	ft_free_split(strs);
	if (pipeline->next == NULL)
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
	{
		andor = get_pipeline(get_strs(strs, 0));
		ft_free_split(strs);
		return (andor);
	}
	andor = get_andor(get_strs(strs, i));
	if (andor == NULL)
	{
		ft_free_split(strs);
		return (NULL);
	}
	/*if (ft_strchr(strs[i + 1], '&'))
	**	andor.? = AND;
	**else
	**	andor.? = PIPELINE;*/
	andor->next = get_andor(get_strs(strs + i + 1, 0));
	ft_free_split(strs);
	if (andor->next == NULL)
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
	{
		list = get_andor(get_strs(strs, 0));
		ft_free_split(strs);
		return (list);
	}
	list = get_list(get_strs(strs, i));
	if (list == NULL)
	{
		ft_free_split(strs);
		return (NULL);
	}
	if (ft_strchr(strs[i], ';'))
		list->op = SCOLON;
	/*else
	**	list->op = AND;*/
	list->next = get_list(get_strs(strs + i + 1, 0));
	ft_free_split(strs);
	if (list->next == NULL)
		return (wrap_free_commands_list(list));
	return (list);
}

t_command			*parse(char **strs)
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
		cmds = get_list(get_strs(strs, 0));
	if (cmds == NULL)
		return (NULL);
	head = cmds;
	while (cmds->next)
		cmds = cmds->next;
	if (ft_strchr(last, ';'))
		cmds->op = SCOLON;
	/*if (ft_strchr(last, '&'))
	**	cmds->op = AND;*/
	return (head);
}
