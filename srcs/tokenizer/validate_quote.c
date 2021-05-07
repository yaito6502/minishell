#include "minishell.h"

/*
** lineのクォートが閉じているかの判定
*/

static void	print_error(char quote)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `", \
	STDERR_FILENO);
	ft_putchar_fd(quote, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}

bool	validate_quote(char *line)
{
	char	quote;

	while (*line != '\0')
	{
		if (*line == '\'' || *line == '"')
		{
			quote = *line;
			line++;
			while (*line != '\0')
			{
				if (*line == quote)
					break ;
				line++;
			}
			if (*line == '\0')
			{
				print_error(quote);
				return (false);
			}
		}
		line++;
	}
	return (true);
}
