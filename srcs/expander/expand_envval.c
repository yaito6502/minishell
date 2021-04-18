#include "minishell.h"

/*
** get_key修正
*/

static int	has_dollar(char *line)
{
	int		ret;
	bool	inquote;

	ret = 0;
	inquote = false;
	while (*line != '\0')
	{
		if (*line == '"' && inquote == false)
			inquote = true;
		else if (*line == '"' && inquote == true)
			inquote = false;
		if (*line == '$' && *(line + 1) != '\0')
			ret++;
		if (*line == '\'' && inquote == false)
		{
			line++;
			while (*line != '\'' && *line != '\0')
				line++;
			if (*line != '\0')
				line++;
		}
		else if (*line != '\0')
			line++;
	}
	return (ret);
}

static char	*copy_literal(char *line, char *ret, int *i)
{
	char	*tmp;
	char	*literal;

	*i = 1;
	while (line[*i] != '\'')
		(*i)++;
	literal = ft_substr(line, 0, *i + 1);
	if (literal == NULL)
		return (NULL);
	tmp = ret;
	ret = ft_strjoin(ret, literal);
	free(literal);
	free(tmp);
	return (ret);
}

static char	*copy_normalchar(char *line, char *ret, int *i, bool inquote)
{
	char	*tmp;
	char	*str;

	*i = 0;
	if (inquote == true)
		while (line[*i] != '\0' && line[*i] != '$')
			(*i)++;
	else
		while (line[*i] != '"' && line[*i] != '\''
			&& line[*i] != '\0' && line[*i] != '$')
			(*i)++;
	str = ft_substr(line, 0, *i);
	if (str == NULL)
		return (NULL);
	tmp = ret;
	ret = ft_strjoin(ret, str);
	free(str);
	free(tmp);
	(*i)--;
	return (ret);
}

static char	*get_key(char *line, char *ret, int *i)
{
	char	*tmp;
	char	*name;
	char	*env;

	*i = 0;
	line++;
	if (*line == '\0')
		return (output_dollar(ret, i));
	if (*line == '?')
		return (expand_exitstatus(ret, i));
	get_envname(line, i);
	name = ft_substr(line, 0, *i);
	if (name == NULL)
		return (NULL);
	env = getenv(name);
	free(name);
	tmp = ret;
	ret = ft_strjoin(ret, env);
	free(tmp);
	return (ret);
}

char	*expand_envval(char *line)
{
	char	*ret;
	int		i;
	bool	inquote;

	inquote = false;
	if (has_dollar(line) == 0)
		return (line);
	ret = NULL;
	while (*line != '\0')
	{
		if (*line == '"' && inquote == false)
			inquote = true;
		else if (*line == '"' && inquote == true)
			inquote = false;
		if (*line == '\'' && inquote == false)
			ret = copy_literal(line, ret, &i);
		else if (*line == '$')
			ret = get_key(line, ret, &i);
		else
			ret = copy_normalchar(line, ret, &i, inquote);
		if (ret == NULL)
			return (NULL);
		line = line + i + 1;
	}
	return (expand_envval(ret));
}
