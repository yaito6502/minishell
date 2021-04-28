#include "minishell.h"

static int	get_len(char *line)
{
	int	len;

	len = 0;
	while (*line)
	{
		if (*line == '\\')
		{
			line++;
			continue ;
		}
		len++;
		line++;
	}
	return (len);
}

char	*get_escapestr(char *line)
{
	char	*str;
	int		len;
	int		i;

	len = get_len(line);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (*line != '\0')
	{
		if (*line == '\\')
		{
			line++;
			continue ;
		}
		str[i] = *line;
		i++;
		line++;
	}
	str[i] = '\0';
	return (str);
}
