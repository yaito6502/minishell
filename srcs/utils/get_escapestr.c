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
	int		i;
	int		j;

	str = malloc(sizeof(char) * (get_len(line) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (line[j] != '\0')
	{
		if (line[j] == '\\' && !is_inquote(line, j))
		{
			j++;
			continue ;
		}
		str[i] = line[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}
