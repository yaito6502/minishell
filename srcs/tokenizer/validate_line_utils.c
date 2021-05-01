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