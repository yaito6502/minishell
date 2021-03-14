#include "minishell.h"

#define SPACES " \t\n\v\f\r"

/*
**関数分け、行数制限などの点でnorm未対応です。
**get_andor()関数はbonusの範囲なのでコメントアウトしてあります
**srcs/utils/内に複数文字でsplitできるft_split_multi.cを追加しています
**各関数の動作はBNFにしたがってよりしたの関数を呼ぶようにしています
*/

t_command	*get_commandline(char *line)
{
	t_command	*cmds_head;
	t_command	*cmds;
	char		*head;

	printf("%s\n", line);
	if (!line)
		return (NULL);
	if ((line = ft_strtrim(line, SPACES)) == NULL)
		return (NULL);
	head = line + ft_strlen(line) - 1;
	if (*head && head[1] != '\0')
		return (NULL);
	head++;
	if (head)
		head = ft_substr(line, 0, head - line);
	else
		head = line;
	if ((cmds = get_list(head)) == NULL)
		return (NULL);
	cmds_head = cmds;
	while (cmds->next)
		cmds = cmds->next;
	cmds->op = SCOLON;
	return (cmds_head);
}

t_command	*get_list(char *line)
{
	t_command			*list_head;
	t_command			*list;
	char				*head;

	printf("list[%s]\n", line);
	if (!line)
		return (NULL);
	if ((head = ft_strrchr(line, ';')) == NULL)
		return (get_pipeline(line));
	if ((list = get_list(ft_substr(line, 0, head - line))) == NULL)
		return (NULL);
	list_head = list;
	while (list->next)
		list = list->next;
	list->op = SCOLON;
	if ((list->next = get_pipeline(head + 1)) == NULL)
	{
		free_commandslist(&list_head);
		return (NULL);
	}
	return (list_head);
}

/*
**後ろから探索するように変更を加える必要あり
*/
/*t_command	*get_andor(char *line)
{
	t_command	*andor;
	char		*head;
	char		*and;
	char		*or;

	if (!line)
		return (NULL);
	and = ft_strnstr(line, "&&", ft_strlen(line));
	or = ft_strnstr(line, "||", ft_strlen(line));
	if (and && (and < or || !or))
		head = and;
	if (or && (or <= and || !and))
		head = or;
	else
		return (get_pipeline(line));
	if ((andor = get_andor(ft_substr(head, 0, (head - 1) - line))) == NULL)
		return (NULL);
	if ((andor->next = get_pipeline(head + 2)) == NULL)
	{
		free_commandslist(&andor);
		return (NULL);
	}
	return (andor);
}*/

t_command	*get_pipeline(char *line)
{
	t_command	*pipeline_head;
	t_command	*pipeline;
	char		*head;

	printf("pipeline[%s]\n", line);
	if (!line)
		return (NULL);
	if ((head = ft_strrchr(line, '|')) == NULL)
		return (get_command(line));
	if ((pipeline = get_pipeline(ft_substr(line, 0, head - line))) == NULL)
		return (NULL);
	pipeline_head = pipeline;
	while (pipeline->next)
		pipeline = pipeline->next;
	pipeline->op = PIPELINE;
	if ((pipeline->next = get_command(head + 1)) == NULL)
	{
		free_commandslist(&pipeline_head);
		return (NULL);
	}
	pipeline->next->receive_pipe = true;
	return (pipeline_head);
}

t_command	*get_command(char *line)
{
	t_command	*cmd;
	char		**words;
	char		**files;
	char		**argv;
	int			i = 0;

	printf("command[%s]\n", line);
	if (!line)
		return (NULL);
	if ((cmd = create_new_tcommand()) == NULL)
		return (NULL);
	if ((words = ft_split(line, ' ')) == NULL)
		return (NULL);
	argv = NULL;
	while (*words != NULL)
	{
		files = NULL;
		files = get_redirection_list(*words++, files);
		if (files == NULL)
			return (NULL);
		while (*files != NULL)
			argv = add_str(argv, *files++);
	}
	while (*argv != NULL)
	{
		if (*argv[0] == '<')
		{
			cmd->redirect_in = add_str(cmd->redirect_in, *argv++);
			cmd->redirect_in = add_str(cmd->redirect_in, *argv++);
		}
		else if (*argv[0] == '>')
		{
			cmd->redirect_out = add_str(cmd->redirect_out, *argv++);
			cmd->redirect_out = add_str(cmd->redirect_out, *argv++);
		}
		else
			cmd->argv = add_str(cmd->argv, *argv++);
	}
	return (cmd);
}

char	**get_redirection_list(char *line, char **argv)
{
	char *head;
	char **files;
	int i;

	printf("redirection[%s]\n", line);
	if (!line)
		return (NULL);
	head = line + ft_strlen(line) - 1;
	while ((head != line) && !ft_strchr("<>", *head))
		head--;
	if (head == line)
	{
		argv = add_str(argv, line);
		return (argv);
	}
	get_redirection_list(ft_substr(line, 0, head - line), files);
	while (*files != NULL)
		argv = add_str(argv, *files++);
	if (*head == '<')
		argv = add_str(argv, "<");
	else
	{
		if (head[1] == '>')
			argv = add_str(argv, ">>");
		else
			argv = add_str(argv, ">");
	}
	return (argv = add_str(argv, head + 1 + (head[1] == '>')));
}

char	**add_str(char **str, char *add)
{
	int			i;
	char		*new_value;
	char		**array;

	if (!str)
	{
		if ((str = (char **)malloc(sizeof(char *))) == NULL)
			return (NULL);
		str[0] = NULL;
	}
	if ((new_value = ft_strdup(add)) == NULL)
		return (NULL);
	i = 0;
	while (str[i] != NULL)
		i++;
	str = (char **)ft_realloc(str, (i + 2) * sizeof(char *));
	str[i] = new_value;
	str[i + 1] = NULL;
	return (str);
}
