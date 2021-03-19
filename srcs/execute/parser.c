#include "minishell.h"

/*
**
**
*/

static char			*get_laststr(char **list)
{
	size_t i;

	if (!list)
		return (NULL);
	i = 0;
	while (list[i] != NULL)
		i++;
	return (list[i - 1]);
}

static char			**get_strs(char **list, int len)
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

static void			set_op(t_command *cmd, t_op op)
{
	t_command *current;

	if (!cmd)
		return ;
	current = cmd;
	while (current->next != NULL)
		current = current->next;
	current->op = op;
}

void				print_strs(char **strs)
{
	size_t i;

	if (!strs)
	{
		puts("NULL");
		return ;
	}
	i = 0;
	while (strs[i] != NULL)
	{
		printf("%s ", strs[i]);
		i++;
	}
	puts("");
}

void				*wrap_free_commands_list(t_command *cmds)
{
	free_commandslist(&cmds);
	return (NULL);
}

static bool			set_redirection_list(t_command *cmd, char **list)
{
	printf("\nredirection_list\n");
	printf("%s %s\n", list[0], list[1]);
	if (ft_strchr(*list, '<'))
	{
		if (!(cmd->redirect_in = add_str_to_list(cmd->redirect_in, list[0])))
			return (false);
		if (!(cmd->redirect_in = add_str_to_list(cmd->redirect_in, list[1])))
			return (false);
	}
	else if (ft_strchr(*list, '>'))
	{
		if (!(cmd->redirect_out = add_str_to_list(cmd->redirect_out, list[0])))
			return (false);
		if (!(cmd->redirect_out = add_str_to_list(cmd->redirect_out, list[1])))
			return (false);
	}
	return (true);
}

static t_command	*get_command(char **list)
{
	size_t				i;
	t_command			*cmd;

	printf("\ncommand\n");
	print_strs(list);
	if (!list)
		return (NULL);
	if ((cmd = create_new_tcommand()) == NULL)
		return (NULL);
	i = 0;
	while (list[i] != NULL)
	{
		if (ft_strchr(list[i], '<') || ft_strchr(list[i], '>'))
		{
			if (!set_redirection_list(cmd, list + i))
				return (wrap_free_commands_list(cmd));
			i += 2;
		}
		else
		{
			if ((cmd->argv = add_str_to_list(cmd->argv, list[i])) == NULL)
				return (wrap_free_commands_list(cmd));
			i++;
		}
	}
	return (cmd);
}

/*
**今のところrecieve_pipeをtrueにする方法が見つからず
*/
static t_command	*get_pipeline(char **list)
{
	size_t				i;
	t_command			*cmd;
	t_command			*head;

	printf("\npipeline\n");
	print_strs(list);
	if (!list)
		return (NULL);
	i = 0;
	head = cmd;
	while (list[i] != NULL)
	{
		if (!ft_strncmp(list[i], "|", 2))
		{
			if ((cmd = get_command(get_strs(list, i))) == NULL)
				return (wrap_free_commands_list(head));
			//set_op(cmd, PIPELINE);
			cmd = cmd->next;
			list += (i + 1);
			i = 0;
		}
		i++;
	}
	if ((cmd = get_command(get_strs(list, 0))) == NULL)
		return (wrap_free_commands_list(head));
	//printf("\npipeline\n");
	return (head);
}

static t_command	*get_andor(char **list)
{
	size_t				i;
	t_command			*cmd;
	t_command			*head;

	printf("\nandor\n");
	print_strs(list);
	if (!list)
		return (NULL);
	i = 0;
	head = cmd;
	while (list[i] != NULL)
	{
		if ((!ft_strncmp(list[i], "&", 2) && !ft_strncmp(list[i + 1], "&", 2)) \
		|| (!ft_strncmp(list[i], "|", 2) && !ft_strncmp(list[i + 1], "|", 2)))
		{
			if ((cmd = get_pipeline(get_strs(list, i))) == NULL)
				return (wrap_free_commands_list(head));
			/*if (!ft_strncmp(list[i], ";", 2))
			**	set_op(cmd, SCOLON);
			*/
			cmd = cmd->next;
			list += (i + 1);
			i = 0;
		}
		i++;
	}
	if ((cmd = get_pipeline(get_strs(list, 0))) == NULL)
		return (wrap_free_commands_list(head));
	//printf("\nandor\n");
	return (head);
}

/*
**214行目のset_opが正常に動作していない
*/
static t_command	*get_list(char **list)
{
	size_t				i;
	t_command			*cmd;
	t_command			*head;

	printf("\nlist\n");
	print_strs(list);
	if (!list)
		return (NULL);
	i = 0;
	head = cmd;
	while (list[i] != NULL)
	{
		if (!ft_strncmp(list[i], ";", 2) || !ft_strncmp(list[i], "&", 2))
		{
			if ((cmd = get_andor(get_strs(list, i))) == NULL)
				return (wrap_free_commands_list(head));
			/*if (!ft_strncmp(list[i], ";", 2))
			**	set_op(cmd, SCOLON);
			*/
			/*if (!ft_strncmp(list[i], "&", 2))
			**	set_op(cmd, AND);
			*/
			cmd = cmd->next;
			list += (i + 1);
			i = 0;
		}
		i++;
	}
	if ((cmd = get_andor(get_strs(list, i))) == NULL)
		return (wrap_free_commands_list(head));
	//printf("\nlist\n");
	return (head);
}

t_command			*get_commandline(char **list)
{
	t_command	*cmds;
	char		*last;

	printf("\ncommandline\n");
	print_strs(list);
	if (!list)
		return (NULL);
	last = get_laststr(list);
	if (!ft_strncmp(last, ";", 2) || !ft_strncmp(last, "&", 2))
		cmds = get_list(get_strs(list, -1));
	else
		cmds = get_list(list);
	/*if (!ft_strncmp(last, ";", 2))
	**	set_op(cmds, SCOLON);
	*/
	/*if (!ft_strncmp(last, "&", 2))
	**	set_op(cmds, AND);
	*/
	//printf("\ncommandline\n");
	return (cmds);
}
