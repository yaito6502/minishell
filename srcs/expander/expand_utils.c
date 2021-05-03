#include "minishell.h"

char	*expand_exitstatus(char *ret, int *i)
{
	char	*status;
	char	*tmp;

	*i = 1;
	status = ft_itoa(store_exitstatus(LOAD, 0));
	if (status == NULL)
		return (NULL);
	tmp = ret;
	ret = ft_strjoin(ret, status);
	free(status);
	free(tmp);
	return (ret);
}

char	*output_dollar(char *ret, int *i)
{
	char	*tmp;

	*i = 0;
	tmp = ret;
	ret = ft_strjoin(ret, "$");
	free(tmp);
	return (ret);
}

int	get_len(char *line)
{
	int		i;
	int		len;
	char	quote;

	i = 0;
	len = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '\'' && line[i] != '"')
		{
			len++;
			i++;
			continue ;
		}
		quote = line[i];
		i++;
		while (line[i] != '\0' && line[i] != quote)
		{
			len++;
			i++;
		}
		i++;
	}
	return (len);
}

char	*copy_literal(char *arg, char *tmp, int *i)
{
	char	quote;

	quote = arg[*i];
	(*i)++;
	while (arg[*i] != quote)
	{
		*tmp = arg[*i];
		tmp++;
		(*i)++;
	}
	(*i)++;
	return (tmp);
}

char	*trim_quote(char *arg)
{
	int		i;
	char	*tmp;
	char	*ret;

	if (arg == NULL)
		return (NULL);
	tmp = malloc(sizeof(char) * (get_len(arg) + 1));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	ret = tmp;
	while (arg[i] != '\0')
	{
		if (arg[i] == '\'' || arg[i] == '"')
		{
			tmp = copy_literal(arg, tmp, &i);
			continue ;
		}
		*tmp++ = arg[i];
		i++;
	}
	*tmp = '\0';
	return (ret);
}
