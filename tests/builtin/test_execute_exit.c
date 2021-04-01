#include "minishell.h"

int		main(int argc, char **argv)
{
	t_command	*cmd;
	pid_t		pid;
	int			status;

	cmd = get_commandline(argv);
	pid = fork();
	if (pid == 0)
		execute_exit(cmd);
	wait(&status);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	printf("status[%d]\n", status);
	free_commandslist(&cmd);
	return (0);
}
