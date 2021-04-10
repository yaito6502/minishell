#include "minishell.h"

#define SPACES	"\v\r\f\t\n "

void	print_tcommand_iterate(t_command *cmds)
{
	t_command *head;

	head = cmds;
	while (head)
	{
		print_tcommand(*head);
		head = head->next;
		puts("");
	}
}

void	print_strs(char **strs)
{
	size_t i = 0;
	while (strs[i] != NULL)
		printf("%s, ", strs[i++]);
	puts("\n");
}

static char	*check_validline(char *line)
{
	char *tmp;

	if (!line)
		return (NULL);
	tmp = ft_strtrim(line, SPACES);
	if (tmp == NULL)
		return (NULL);
	if (!validate_line(tmp) || !validate_quote(tmp))
	{
		free(tmp);
		free(line);
		return (NULL);
	}
	free(line);
	line = tmp;
	return (line);
}

static int	get_len(char *line)
{
	int		i;
	int		len;
	char	quote;

	i = 0;
	len = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '\'' && line[i] != '"')
		{
			len++;
			i++;
			continue ;
		}
		quote = line[i];
		i++;
		while (line[i] != '\0' && line[i] != quote)
		{
			len++;
			i++;
		}
		i++;
	}
	return (len);
}

static char	*copy_literal(char *arg, char *tmp, int *i)
{
	char	quote;

	quote = arg[*i];
	(*i)++;
	while (arg[*i] != quote)
	{
		*tmp = arg[*i];
		tmp++;
		(*i)++;
	}
	(*i)++;
	return (tmp);
}

static char	*trim_quote(char *arg)
{
	int		i;
	char	*tmp;
	char	*ret;

	tmp = malloc(sizeof(char) * (get_len(arg) + 1));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	ret = tmp;
	while (arg[i] != '\0')
	{
		if (arg[i] == '\'' || arg[i] == '"')
		{
			tmp = copy_literal(arg, tmp, &i);
			continue ;
		}
		*tmp++ = arg[i];
		i++;
	}
	*tmp = '\0';
	return (ret);
}

static bool	preprocess_tokens(char **strs)
{
	int		i;
	char	*ret;
	char	*tmp;

	if (strs == NULL)
		return (true);
	i = 0;
	while (strs[i] != NULL)
	{
		ret = expand_envval(strs[i]);
		if (ret == NULL)
			return (false);
		tmp = ret;
		ret = trim_quote(ret);
		if (tmp != strs[i])
			free(tmp);
		if (ret == NULL)
			return (false);
		free(strs[i]);
		strs[i] = ret;
		i++;
	}
	return (true);
}

int		main(int argc, char **argv)
{
	t_command	*cmd;
	char		**token;
	char		*line;

	puts("");
	line = check_validline(ft_strdup(argv[1]));
	if (line == NULL)
	{
		puts("==========================================================================");
		return (1);
	}
	token = tokenize(line);
	print_strs(token);
	if ((cmd = parse(token)) != NULL)
		print_tcommand_iterate(cmd);
	ft_free_split(token);
	free_commandslist(&cmd);
	//system("leaks test");
	puts("==========================================================================");
	return (0);
}
