#include "minishell.h"

/*
** line中にトークンの不正な連続がないか確認する。
** ;; || & ";[space];" "|[space]|" ";|"
*/

#define AMP		'&'
#define OPS		"|;&<>"
#define SEP		"|;&"
#define SPACES	"\v\r\f\t\n "

static bool	error_return(char *line, char last_op, bool has_space)
{
	const char *newline = "newline";

	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (*line == last_op && !has_space)
	{
		ft_putchar_fd(last_op, STDERR_FILENO);
		ft_putchar_fd(last_op, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
	}
	else
	{
		last_op = *line;
		if (last_op == '\0')
			ft_putstr_fd((char *)newline, STDERR_FILENO);
		else
			ft_putchar_fd(last_op, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
	}
	return (false);
}

static bool	check_operator(char *line, char last_op)
{
	bool	has_space;

	has_space = false;
	line++;
	while (*line != '\0')
	{
		if (!ft_strchr(OPS, *line) && !ft_strchr(SPACES, *line))
			return (true);
		if (ft_strchr(SPACES, *line))
			has_space = true;
		else if (*line == '<')
			return (error_return(line, last_op, (line[1] != '<')));
		else if (line[1] == '>')
			return (error_return(line, last_op, (line[2] != '>')));
		else if (ft_strchr(SEP, *line))
			return (error_return(line, last_op, has_space));
		line++;
	}
	if (last_op == ';')
		return (true);
	else
		return (error_return(line, last_op, false));
}

bool	validate_line(char *line)
{
	while (*line != '\0')
	{
		if (ft_strchr(OPS, *line))
		{
			if (*line == AMP)
				return (error_return(line, 'n', false));
			if (!check_operator(line, *line))
				return (false);
		}
		line++;
	}
	return (true);
}
