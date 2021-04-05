#include "minishell.h"

bool	redirect_error(char *key, char *errmsg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd(": ", 2);
	if (errmsg == NULL)
		ft_putendl_fd(strerror(errno), 2);
	else
		ft_putendl_fd(errmsg, 2);
	return (false);
}

bool	fd_error(long fd, char *errmsg)
{
	ft_putstr_fd("minishell: ", 2);
	if (fd < INT_MAX)
		ft_putnbr_fd((int)fd, 2);
	else
		ft_putstr_fd("file descriptor out of range", 2);
	ft_putstr_fd(": ", 2);
	if (errmsg == NULL)
		ft_putendl_fd(strerror(errno), 2);
	else
		ft_putendl_fd(errmsg, 2);
	return (false);
}
