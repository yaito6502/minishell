#include "minishell.h"

bool	redirect_error(char *key, char *errmsg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(key, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (errmsg == NULL)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	else
		ft_putendl_fd(errmsg, STDERR_FILENO);
	return (false);
}

bool	fd_error(long fd, char *errmsg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (fd < INT_MAX)
		ft_putnbr_fd((int)fd, STDERR_FILENO);
	else
		ft_putstr_fd("file descriptor out of range", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (errmsg == NULL)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	else
		ft_putendl_fd(errmsg, STDERR_FILENO);
	return (false);
}
