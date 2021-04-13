#include "minishell.h"

static int	print_error(char *message)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	return (255);
}

static bool	is_digits(char *str)
{
	size_t	i;

	i = 0;
	if (*str == '-' || *str == '+')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (false);
	return (true);
}

static bool	is_overflow(long long num, int bottom)
{
	if (num > (LLONG_MAX / 10) || num < (LLONG_MIN / 10))
		return (true);
	if (num == (LLONG_MAX / 10) && bottom > (LLONG_MAX % 10))
		return (true);
	if (num == (LLONG_MIN / 10) && bottom < (LLONG_MIN % 10))
		return (true);
	return (false);
}

static long long	ft_atoll(const char *nptr)
{
	int				sign;
	long long		num;
	char			*copy;

	num = 0;
	sign = 1;
	copy = (char *)nptr;
	while (ft_isspace((char)*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			sign = -1;
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (is_overflow(num * sign, (*nptr - '0') * sign))
		{
			sign = print_error(copy);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			wrap_exit(sign);
		}
		num = num * 10 + *nptr - '0';
		nptr++;
	}
	return (sign * num);
}

int	execute_exit(t_command *cmd)
{
	unsigned int	exit_status;
	char			*str;

	str = NULL;
	if (cmd->argv[1] != NULL)
		str = cmd->argv[(!ft_strncmp(cmd->argv[1], "--", 3)) + 1];
	if (str == NULL)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		wrap_exit(EXIT_SUCCESS);
	}
	if (!is_digits(str))
	{
		exit_status = print_error(str);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		wrap_exit(exit_status);
	}
	if (cmd->argv[(!ft_strncmp(cmd->argv[1], "--", 3)) + 2] != NULL)
		wrap_exit(print_error("too many arguments\n"));
	exit_status = ft_atoll(str);
	ft_putendl_fd("exit", STDOUT_FILENO);
	wrap_exit(exit_status % 256);
	return (EXIT_FAILURE);
}
