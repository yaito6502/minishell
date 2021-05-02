#include "minishell.h"

//static bool	is_inquote(char *line)
//{
//	static bool	inquote = false;
//
//	if (*line != '"')
//		return (inquote);
//	if (inquote == false)
//	{
//		inquote = true;
//		return (inquote);
//	}
//	inquote = false;
//	return (inquote);
//}

static char	*copy_singlequote(char *tmp, int *index, char *line)
{
	int i;

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
	int i;

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
	int i;

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

	tmp = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (*line != '\0')
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
