#include "minishell.h"

#define AMP		'&'
#define OPS		"|;&<>"
#define SEP		"|;&"
#define SPACES	"\v\r\f\t\n "

static char	*skip_inquote(char *line, char quote)
{
	line++;
	while (*line != quote)
		line++;
	return (line);
}

static bool	error_return(char *line, char last_op, bool has_space)
{
	const char	*newline = "newline";

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
	store_exitstatus(SAVE, 258);
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

static bool	check_first_segment(char *line)
{
	char	*first_sep;
	char	sep;

	first_sep = get_first_sep(line);
	if (first_sep == NULL)
		return (true);
	sep = *first_sep;
	while (*line != sep)
	{
		if (!ft_strchr(OPS, *line) && !ft_strchr(SPACES, *line))
			return (true);
		line++;
	}
	if (*(first_sep + 1) == sep)
		return (error_return(first_sep, sep, false));
	return (error_return(first_sep, 'a', false));
}

bool	validate_line(char *line)
{
	if (!check_first_segment(line))
		return (false);
	while (*line != '\0')
	{
		if (*line == '"' || *line == '\'')
			line = skip_inquote(line, *line);
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
