#include "minishell.h"

/*
** export
** export [value]
** export [key=value]
*/

static int	print_error(char *message)
{
	ft_putstr_fd("minishell : export: `", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (EXIT_FAILURE);
}

static bool	set_keyvalue(char *str, char **key, char **value)
{
	char	*equal;

	equal = ft_strchr(str, '=');
	*value = NULL;
	if (equal)
	{
		*key = ft_substr(str, 0, equal - str);
		*value = ft_strdup(equal + 1);
	}
	else
		*key = ft_strdup(str);
	if (!*key || (equal && !*value))
	{
		ft_putstr_fd("minishell : export : ", STDERR_FILENO);
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
		if (!update_env(key, value))
			status = print_error(cmd->argv[i]);
		free(key);
		free(value);
		i++;
	}
	return (status);
}
