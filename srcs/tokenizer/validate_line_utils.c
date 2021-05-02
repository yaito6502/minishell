#include "minishell.h"

#define SEP		"|;&"

static char	*return_small(char *a, char *b)
{
	if (a == NULL)
		return (b);
	if (b == NULL)
		return (a);
	if (a < b)
		return (a);
	return (b);
}

char	*get_first_sep(char *line)
{
	char	*first_sep;
	char	*scolon;
	char	*pipe;
	char	*amp;

	scolon = ft_strchr(line, ';');
	pipe = ft_strchr(line, '|');
	amp = ft_strchr(line, '&');
	if (scolon && pipe && amp)
	{
		if (scolon < pipe)
			first_sep = scolon;
		first_sep = pipe;
		return (return_small(first_sep, amp));
	}
	if (!scolon)
		return (return_small(pipe, amp));
	if (!pipe)
		return (return_small(scolon, amp));
	return (return_small(scolon, pipe));
}

bool	error_return(char *line, char last_op, bool has_space)
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
