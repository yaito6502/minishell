#include "minishell.h"

int	error_execute(char *path)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (errno == EFAULT)
		ft_putendl_fd("command not found", STDERR_FILENO);
	else
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	if (errno == EACCES)
		return (126);
	if (errno == ENOENT || errno == EFAULT)
		return (127);
	return (1);
}

int	error_fork(void)
{
	ft_putstr_fd("minishell: fork: ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	return (1);
}
