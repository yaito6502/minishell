#include "minishell.h"

/*
** export
** export [value]
** export [key=value]
*/

static int	print_error(char *message)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (EXIT_FAILURE);
}

static char	*copy_addslash(char *tmp, int *i, char *line)
{
	size_t	slash;

	slash = 0;
	while (*line == '\\')
	{
		line++;
		slash++;
	}
	if (slash >= 1)
		tmp[(*i)++] = '\\';
	tmp[(*i)++] = '\\';
	tmp[(*i)++] = *line;
	line++;
	return (line);
}

static char	*set_value(char *line)
{
	char	*tmp;
	char	*str;
	int		i;

	tmp = malloc(ft_strlen(line) * 2 + 1);
	if (tmp == NULL)
		return (NULL);
	i = 0;
	while (*line)
	{
		if (ft_strchr("\"$\'\\", *line))
			line = copy_addslash(tmp, &i, line);
		else
		{
			tmp[i] = *line;
			i++;
			line++;
		}
	}
	tmp[i] = '\0';
	str = ft_strdup(tmp);
	free(tmp);
	return (str);
}

static bool	set_keyvalue(char *str, char **key, char **value)
{
	char	*equal;
	char	*plus;

	equal = ft_strchr(str, '=');
	*value = NULL;
	if (equal)
	{
		plus = ft_strchr(str, '+');
		*key = ft_substr(str, 0, equal - (str + !!plus));
		if (plus + 1 == equal && getenv(*key))
			*value = ft_strjoin(getenv(*key), equal + 1);
		else
			*value = set_value(equal + 1);
	}
	else
		*key = ft_strdup(str);
	if (!*key || (equal && !*value))
	{
		ft_putstr_fd("minishell: export : ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (false);
	}
	return (true);
}

int	execute_export(t_command *cmd)
{
	size_t	i;
	int		status;
	char	*key;
	char	*value;

	i = 1;
	status = EXIT_SUCCESS;
	if (cmd->argv[1] == NULL)
		return (print_sorted_env());
	while (cmd->argv[i] != NULL)
	{
		key = NULL;
		value = NULL;
		if (!set_keyvalue(cmd->argv[i], &key, &value))
			status = EXIT_FAILURE;
		if (!ft_strncmp(key, "_", 2) || !update_env(key, value))
			status = print_error(cmd->argv[i]);
		free(key);
		free(value);
		i++;
	}
	return (status);
}
