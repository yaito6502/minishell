#include "minishell.h"

/*
** mainからforkした二つの子プロセスでpipeを通して通信するテスト。
*/

int	main(void)
{
	t_command *cmd;
	int newpipe[2];
	pid_t pid;
	int rc;
	char buf[100];

	cmd = create_new_tcommand();
	cmd->next = create_new_tcommand();
	cmd->op = PIPELINE;
	pipe(newpipe);
	pid = fork();
	if (pid == 0)
	{
		write(STDOUT_FILENO, "This message from first child process before piping.\n", 53);
		send_pipeline(cmd, newpipe);
		write(STDOUT_FILENO, "hello, world!\n",14);
		exit(0);
	}
	cmd->next->receive_pipe = true;
	cmd->next->lastfd[0] = newpipe[0];
	cmd->next->lastfd[1] = newpipe[1];
	pid = fork();
	if (pid == 0)
	{
		write(STDOUT_FILENO, "This message from second child process before piping.\n", 54);
		receive_pipeline(cmd->next);
		while ((rc = read(STDIN_FILENO, buf, 1)) != 0)
		{
			write(STDOUT_FILENO, buf, rc);
		}
		exit(0);
	}
	return 0;
}