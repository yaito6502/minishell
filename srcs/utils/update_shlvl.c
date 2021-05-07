#include "minishell.h"

#define SPACES	"\v\r\f\t\n "

static void	output_error(char *val)
{
	ft_putstr_fd("minishell: warning: shell level (", STDERR_FILENO);
	ft_putstr_fd(val, STDERR_FILENO);
	ft_putendl_fd(") too high, resetting to 1", STDERR_FILENO);
	return ;
}

static bool	reset_shlvl(char *new_val, char *old_val)
{
	int	value;

	value = ft_atoi(old_val);
	if (value >= 1001)
		output_error(old_val);
	free(old_val);
	return (update_env("SHLVL", new_val));
}

static bool	is_valid_shlvl(char *env)
{
	if (!ft_isdigit(*env) && *env != '+' && *env != '-')
		return (false);
	env++;
	while (*env != '\0')
	{
		if (!ft_isdigit(*env))
			return (false);
		env++;
	}
	return (true);
}

bool	update_shlvl(void)
{
	char	*env;
	char	*tmp;
	int		value;
	bool	ret;

	env = getenv("SHLVL");
	while (env && ft_strchr(SPACES, *env))
		env++;
	env = ft_strtrim(env, "\t\n ");
	if (env == NULL || !is_valid_shlvl(env))
		return (reset_shlvl("1", env));
	value = ft_atoi(env);
	if (value < 0)
		return (reset_shlvl("0", env));
	value++;
	tmp = env;
	env = ft_itoa(value);
	free(tmp);
	if (env == NULL)
		return (false);
	if (value >= 1001)
		return (reset_shlvl("1", env));
	ret = update_env("SHLVL", env);
	free(env);
	return (ret);
}
