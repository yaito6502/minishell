#include "minishell.h"

static char	*copy_singlequote(char *tmp, int *index, char *line)
{
	int	i;

	i = *index;
	tmp[i] = *line;
	line++;
	i++;
	while (*line != '\'')
	{
		tmp[i] = *line;
		line++;
		i++;
	}
	tmp[i] = *line;
	line++;
	i++;
	*index = i;
	return (line);
}

static char	*copy_doublequote(char *tmp, int *index, char *line)
{
	int	i;

	i = *index;
	tmp[i] = *line;
	line++;
	i++;
	while (*line != '"')
	{
		if (*line == '\\' && *(line + 1) == '\\')
			line++;
		tmp[i] = *line;
		line++;
		i++;
	}
	tmp[i] = *line;
	line++;
	i++;
	*index = i;
	return (line);
}

static char	*copy_outquote(char *tmp, int *index, char *line)
{
	int	i;

	i = *index;
	while (*line != '\0' && *line != '\'' && *line != '"')
	{
		if (*line == '\\' && *(line + 1) != '\\')
		{
			line++;
			continue ;
		}
		if (*line == '\\' && *(line + 1) == '\\')
			line++;
		tmp[i] = *line;
		line++;
		i++;
	}
	*index = i;
	return (line);
}

char	*get_escapestr(char *line)
{
	char	*tmp;
	char	*str;
	int		i;
	int		j;

	tmp = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (line[j] != '\0')
	{
		if (*line == '\'')
			line = copy_singlequote(tmp, &i, line);
		else if (*line == '"')
			line = copy_doublequote(tmp, &i, line);
		else
			line = copy_outquote(tmp, &i, line);
	}
	tmp[i] = '\0';
	str = ft_strdup(tmp);
	free(tmp);
	return (str);
}
