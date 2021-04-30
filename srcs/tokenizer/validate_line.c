#include "minishell.h"

/*
** line中にトークンの不正な連続がないか確認する。
** ;; || & ";[space];" "|[space]|" ";|"
*/

#define AMP		'&'
#define OPS		"|;&<>"
#define SEP		"|;&"
#define SPACES	"\v\r\f\t\n "

static size_t	count_consective_char(char *line)
{
	size_t	i;
	char	head;

	i = 0;
	head = *line;
	while (*line && line[i] == head)
		i++;
	return (i);
}

static bool	error_return(char *line, char *prev_ptr)
{
	const char	*newline = "newline";
	size_t		i;

	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	i = count_consective_char(prev_ptr);
	if (ft_strchr(SEP, *prev_ptr) && i >= 2)
		i = 2;
	if (*prev_ptr == '<' && line != prev_ptr)
		i = i % 2 + 1;
	if (*prev_ptr == '>' && line != prev_ptr)
		i = i % 3 + 1;
	if (ft_strchr("<>", *prev_ptr) && !*line)
		ft_putstr_fd((char *)newline, STDERR_FILENO);
	else
		while (i--)
			ft_putchar_fd(*prev_ptr, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	store_exitstatus(SAVE, 258);
	return (false);
}

static bool	check_operator(char *line)
{
	char	*prev_ptr;

	while (*line != '\0')
	{
		prev_ptr = line;
		line++;
		if (!ft_strchr(OPS, *line) && !ft_strchr(SPACES, *line))
			return (true);
		if (ft_strchr(SPACES, *line))
		{
			line++;
			if (ft_strchr("<>", *prev_ptr) && ft_strchr(OPS, *line))
				return (error_return(line, line));
			continue ;
		}
		if (*prev_ptr == '>' && count_consective_char(prev_ptr) > 2)
			return (error_return(line, prev_ptr));
		if (ft_strchr("|;&<", *line) && *line != *prev_ptr)
			prev_ptr = line;
		if (ft_strchr("|;&<", *line))
			return (error_return(line, prev_ptr));
	}
	if (*prev_ptr == ';')
		return (true);
	return (error_return(line, prev_ptr));
}

bool	validate_line(char *line)
{
	char	*head;

	head = line;
	while (*line != '\0')
	{
		if (ft_strchr(OPS, *line))
		{
			if (line == head && !ft_strchr("<>", *line))
				return (error_return(line, line));
			if (*line == AMP)
				return (error_return(line, line));
			if (!check_operator(line))
				return (false);
		}
		line++;
	}
	return (true);
}
