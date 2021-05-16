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

static bool	check_redirect(char *line)
{
	while (*line != '\0')
	{
		if (!ft_strchr(OPS, *line) && !ft_strchr(SPACES, *line))
			return (true);
		if (ft_strchr(SEP, *line))
			return (error_return(line, 'a', false));
		if (ft_strchr("<>", *line))
		{
			if (*(line + 1) == *line)
				return (error_return(line, *line, false));
			return (error_return(line, 'a', false));
		}
		line++;
	}
	return (error_return(line, 'a', false));
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
		else if (ft_strchr("<>", *line) && last_op == *line && !has_space)
			return (check_redirect(line + 1));
		else if (ft_strchr("<>", *line) && last_op != ';' && last_op != '|')
			return (error_return(line, last_op, has_space));
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
