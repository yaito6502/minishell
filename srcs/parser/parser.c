#include "minishell.h"

static bool	set_redirection_list(t_command *cmd, char **list)
{
	char	**target;

	target = NULL;
	if (ft_strchr(*list, '<'))
		target = cmd->redirect_in;
	else if (ft_strchr(*list, '>'))
		target = cmd->redirect_out;
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

static t_command	*get_command(char **strs)
{
	int			i;
	t_command	*cmd;

	cmd = create_new_tcommand();
	if (!strs || !cmd)
		return (NULL);
	i = 0;
	while (strs[i] != NULL)
	{
		if (endswith(strs[i], "<") || endswith(strs[i], ">"))
		{
			if (!set_redirection_list(cmd, strs + i))
				return (free_commandslist(&cmd));
			i += 2;
		}
		else
		{
			cmd->argv = add_str_to_list(cmd->argv, strs[i++]);
			if (cmd->argv == NULL)
				return (free_commandslist(&cmd));
		}
	}
	return (cmd);
}

static t_command	*get_pipeline(char **strs)
{
	int			i;
	t_command	*pipeline;
	t_command	*last;

	if (!strs)
		return (NULL);
	i = strsncmp(strs, "|");
	if (i < 0)
	{
		pipeline = get_command(strs);
		ft_free_split(strs);
		return (pipeline);
	}
	pipeline = get_pipeline(get_strs(strs, i));
	if (pipeline == NULL)
		return (ft_free_split(strs));
	pipeline->op = PIPELINE;
	last = get_lastcommand(pipeline);
	last->next = get_pipeline(get_strs(strs + i + 1, 0));
	ft_free_split(strs);
	if (last->next == NULL)
		return (free_commandslist(&pipeline));
	last->next->receive_pipe = true;
	return (pipeline);
}

// for bonus
/*static t_command	*get_andor(char **strs)
{
	int			i;
	t_command	*andor;
	t_command	*last;

	if (!strs)
		return (NULL);
	i = strsncmp(strs, "&|");
	if (i < 0 || (ft_strncmp(strs, "&&", 3) && ft_strncmp(strs, "||", 3)))
	{
		andor = get_pipeline(get_strs(strs, 0));
		ft_free_split(strs);
		return (andor);
	}
	andor = get_andor(get_strs(strs, i));
	if (andor == NULL)
		return (wrap_ft_free_split(strs));
	last = get_lastcommand(andor);
	last->next = get_andor(get_strs(strs + i + 1, 0));
	ft_free_split(strs);
	if (last->next == NULL)
		return (wrap_free_commands_list(andor));
	return (andor);
}*/

static t_command	*get_list(char **strs)
{
	int			i;
	t_command	*list;
	t_command	*last;

	if (!strs)
		return (NULL);
	i = strsncmp(strs, ";");
	if (i < 0)
	{
		list = get_pipeline(get_strs(strs, 0));
		ft_free_split(strs);
		return (list);
	}
	list = get_list(get_strs(strs, i));
	if (list == NULL)
		return (ft_free_split(strs));
	list->op = SCOLON;
	last = get_lastcommand(list);
	last->next = get_list(get_strs(strs + i + 1, 0));
	ft_free_split(strs);
	if (last->next == NULL)
		return (free_commandslist(&list));
	return (list);
}

t_command	*parse(char **strs)
{
	t_command	*cmds;
	t_command	*last_cmd;
	size_t		i;
	char		*last_str;

	if (!strs)
		return (NULL);
	i = 0;
	while (strs[i] != NULL)
		i++;
	last_str = strs[i - 1];
	if (!ft_strncmp(last_str, ";", 2))
		cmds = get_list(get_strs(strs, -1));
	else
		cmds = get_list(get_strs(strs, 0));
	if (cmds == NULL)
	{
		ft_putendl_fd("minishell: parser: malloc error", STDERR_FILENO);
		return (NULL);
	}
	last_cmd = get_lastcommand(cmds);
	last_cmd->op = SCOLON;
	return (cmds);
}
