#include "minishell.h"

#define SPACES	"\v\r\f\t\n"

static bool	error_ambiguous(char *str)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
	return (false);
}

static bool	check_token(char *token)
{
	int		i;
	char	*env;

	if (token[0] != '$')
		return (true);
	i = 1;
	while (ft_isalnum(token[i]) || token[i] == '_')
		i++;
	if (token[i] != '\0')
		return (true);
	env = getenv(token + 1);
	if (env == NULL)
		return (false);
	while (*env != '\0')
	{
		if (ft_strchr(SPACES, *env))
			return (false);
		env++;
	}
	return (true);
}

static bool	check_list(char **list)
{
	int	i;

	i = 0;
	while (list[i] != NULL)
	{
		i++;
		if (!check_token(list[i]))
			return (error_ambiguous(list[i]));
		i++;
	}
	return (true);
}

bool	validate_redirect(t_command *cmd)
{
	bool	ret;

	ret = true;
	if (cmd->redirect_in != NULL)
		ret = check_list(cmd->redirect_in);
	if (ret == false)
		return (false);
	if (cmd->redirect_out != NULL)
		ret = check_list(cmd->redirect_out);
	if (ret == false)
		return (false);
	return (true);
}
