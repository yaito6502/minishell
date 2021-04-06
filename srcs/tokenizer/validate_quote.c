#include "minishell.h"

/*
** lineのクォートが閉じているかの判定
*/

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
				ft_putendl_fd("minishell: Quote is not closed.", 2);
				return (false);
			}
		}
		line++;
	}
	return (true);
}
