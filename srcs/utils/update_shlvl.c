#include "minishell.h"

static void	output_error(char *val)
{
	ft_putstr_fd("minishell: warning: shell level (", STDERR_FILENO);
	ft_putstr_fd(val, STDERR_FILENO);
	ft_putendl_fd(") too high, resetting to 1", STDERR_FILENO);
	return ;
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
	extern char	**environ;
	char		*env;
	int			value;
	bool		ret;

	env = getenv("SHLVL");
	if (env == NULL)
		return (add_newval_to_env("SHLVL=1"));
	if (!is_valid_shlvl(env))
		return (update_env("SHLVL", "1"));
	value = ft_atoi(env);
	if (value < 0)
		return (update_env("SHLVL", "0"));
	if (++value == 1000)
		return (update_env("SHLVL", ""));
	env = ft_itoa(value);
	if (value >= 1001)
	{
		output_error(env);
		free(env);
		return (update_env("SHLVL", "1"));
	}
	ret = update_env("SHLVL", env);
	free(env);
	return (ret);
}
