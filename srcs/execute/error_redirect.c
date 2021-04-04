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
	char	*str;

	if (fd < INT_MAX)
		str = ft_ltoa(fd);
	else
		str = ft_strdup("file descriptor out of range");
	if (!str)
		return (false);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	if (errmsg == NULL)
		ft_putendl_fd(strerror(errno), 2);
	else
		ft_putendl_fd(errmsg, 2);
	free(str);
	return (false);
}
