#include "minishell.h"

int		error_execute(char *path)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	if (errno == EFAULT)
		ft_putendl_fd("command not found", 2);
	else
		ft_putendl_fd(strerror(errno), 2);
	if (errno == EACCES)
		return (126);
	if (errno == EFAULT)
		return (127);
	return (1);
}
