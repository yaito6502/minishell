#include "minishell.h"

static void	parallel_childproc(t_command *cmd, int newpipe[2])
{
	extern char	**environ;
	int			ret;

	send_pipeline(cmd, newpipe);
	receive_pipeline(cmd);
	redirect_input(cmd);
	redirect_output(cmd);
	if (is_builtin(cmd) != -1)
	{
		execute_builtin(cmd);
		exit(cmd->exitstatus);
	}
	if (has_slash(cmd->argv[0]))
		ret = execve(cmd->argv[0], cmd->argv, environ);
	else
		ret = execve(get_cmd_frompath(cmd), cmd->argv, environ);
	ret = error_execute(cmd->argv[0]);
	exit(ret);
}

void		execute_parallel(t_command *cmd)
{
	int			newpipe[2];

	if (cmd->op == PIPELINE)
		pipe(newpipe);
	cmd->pid = fork();
	if (cmd->pid == 0)
		parallel_childproc(cmd, newpipe);
	cmd->has_childproc = true;
	if (cmd->receive_pipe == true)
	{
		close(cmd->lastfd[0]);
		close(cmd->lastfd[1]);
	}
	if (cmd->op == PIPELINE)
	{
		cmd->next->lastfd[0] = newpipe[0];
		cmd->next->lastfd[1] = newpipe[1];
	}
	return ;
}
