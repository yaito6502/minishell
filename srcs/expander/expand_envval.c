#include "minishell.h"

static int	has_dollar(char *line)
{
	int		ret;

	ret = 0;
	while (*line != '\0')
	{
		if (*line == '"')
			is_inquote(*line);
		if (*line == '$' && *(line + 1) != '\0'
			&& !ft_isspace(*(line + 1)) && *(line + 1) != '"')
			ret++;
		if (*line == '\'' && !is_inquote('L'))
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
	if (line[*i] == '"')
		(*i)++;
	if (inquote == true)
		while (line[*i] != '"' && line[*i] != '\0' && line[*i] != '$')
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
	if (*line == '\0' || ft_isspace(*line) || *line == '"')
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

	if (has_dollar(line) == 0)
		return (line);
	ret = NULL;
	while (*line != '\0')
	{
		if (*line == '"')
			is_inquote(*line);
		if (*line == '\'' && !is_inquote('L'))
			ret = copy_literal(line, ret, &i);
		else if (*line == '$')
			ret = get_key(line, ret, &i);
		else
			ret = copy_normalchar(line, ret, &i, is_inquote('L'));
		if (ret == NULL)
			return (NULL);
		line = line + i + 1;
	}
	return (expand_envval(ret));
}
