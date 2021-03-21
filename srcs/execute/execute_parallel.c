#include "minishell.h"

static void	execute_child(t_command *cmd, int newpipe[2])
{
	extern char	**environ;

	send_pipeline(cmd, newpipe);
	receive_pipeline(cmd);
	redirect_input(cmd);
	redirect_output(cmd);
	if (is_builtin(cmd) != -1)
	{
		//execute_builtin(cmd);
		printf("this command is builtin.\n");
		exit(EXIT_SUCCESS) ;//call exit func
	}
	if (has_slash(cmd->argv[0]))
		execve(join_path(cmd->argv[0]), cmd->argv, environ);
	execve(get_cmd_frompath(cmd), cmd->argv, environ);
}

void		execute_parallel(t_command *cmd)
{
	int			status;
	int			newpipe[2];

	if (cmd->op == PIPELINE)
		pipe(newpipe);
	cmd->pid = fork();
	if (cmd->pid == 0)
		execute_child(cmd, newpipe);
	if (cmd->receive_pipe == true)
	{
		close(cmd->lastfd[0]);
		close(cmd->lastfd[1]);
	}
	if (cmd->op == PIPELINE)
	{
		cmd->next->receive_pipe = true;
		cmd->next->lastfd[0] = newpipe[0];
		cmd->next->lastfd[1] = newpipe[1];
	}
	return ;
}
