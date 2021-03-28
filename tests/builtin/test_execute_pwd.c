#include "minishell.h"

int		main(void)
{
	t_command	*cmd;
	int			status;

	status = execute_pwd(cmd);
	printf("status[%d]\n", status);
	return (0);
}
