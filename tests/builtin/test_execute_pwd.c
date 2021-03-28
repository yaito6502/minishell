#include "minishell.h"

int		main(void)
{
	t_command	*cmd;
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid == 0)
		execute_pwd(cmd);
	else
	{
		wait(&status);
		printf("%s\n", strerror(status));
	}
	return (0);
}
