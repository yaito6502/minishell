#include "minishell.h"

int	error_execute(char *path, int last_errno)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (last_errno == EFAULT)
		ft_putendl_fd("command not found", STDERR_FILENO);
	else
		ft_putendl_fd(strerror(last_errno), STDERR_FILENO);
	if (last_errno == EACCES)
		return (126);
	if (last_errno == ENOENT || last_errno == EFAULT)
		return (127);
	return (1);
}

int	error_fork(void)
{
	ft_putstr_fd("minishell: fork: ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	return (1);
}

int	error_dir(char *path)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putendl_fd(": is a directory", STDERR_FILENO);
	return (126);
}
