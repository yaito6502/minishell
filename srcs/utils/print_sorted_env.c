#include "minishell.h"

static char	*create_escaped_str(char *str)
{
	char	*tmp;
	char	*esc;
	int		i;

	tmp = malloc(ft_strlen(str) * 2 + 1);
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (ft_strchr("\"$\'\\", *str))
		{
			tmp[i++] = '\\';
			tmp[i++] = *str++;
			if (str && ft_strchr("\"$\'", *str))
				tmp[i++] = *str++;
		}
		else
			tmp[i++] = *str++;
	}
	tmp[i] = '\0';
	esc = ft_strdup(tmp);
	free(tmp);
	return (esc);
}

static bool	get_str_literal(char *str, char **literal)
{
	char	*equal;

	*literal = NULL;
	equal = ft_strchr(str, '=');
	if (!equal)
		return (false);
	*literal = create_escaped_str(equal + 1);
	*literal = ft_str_sandwich(*literal, "\"");
	*literal = ft_strjoin("=", *literal);
	return (true);
}

char	**get_sorted_environ(void)
{
	extern char	**environ;
	char		**sorted;
	char		**buf;
	size_t		i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	sorted = (char **)malloc(sizeof(char *) * (i + 1));
	buf = (char **)malloc(sizeof(char *) * (i + 1));
	if (!sorted || !buf)
	{
		free(sorted);
		free(buf);
		return (NULL);
	}
	ft_memcpy(sorted, environ, sizeof(char *) * (i + 1));
	sorted[i] = NULL;
	sort_environ(sorted, buf, 0, i);
	free(buf);
	return (sorted);
}

int	print_sorted_env(void)
{
	char	**sorted;
	char	*value;
	bool	has_value;
	size_t	i;

	sorted = get_sorted_environ();
	if (sorted == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (sorted[i] != NULL)
	{
		has_value = get_str_literal(sorted[i], &value);
		if (has_value && !value)
			return (EXIT_FAILURE);
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		while (*sorted[i] && *sorted[i] != '=')
			ft_putchar(*sorted[i]++);
		if (has_value)
			ft_putstr_fd(value, STDOUT_FILENO);
		free(value);
		ft_putendl_fd("", STDOUT_FILENO);
		i++;
	}
	free(sorted);
	return (EXIT_SUCCESS);
}
