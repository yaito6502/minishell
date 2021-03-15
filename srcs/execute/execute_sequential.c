#include "minishell.h"


//エラー時、bool型等を返して判定する？
void		execute_sequential(t_command *cmd)
{
	pid_t	pid;
	extern	char **environ;
	char	*path;

	//修正前なので、コメントアウトしてます。
	//redirect_input(cmd);
	//redirect_output(cmd);
	if (is_builtin(cmd) != -1)
	{
		//execute_builtin(cmd);
		printf("this command is builtin.\n");
		return ;
	}
	if ((pid = fork()) == -1)
		;//error
	if (pid == 0)
		execve(get_cmd_frompath(cmd), cmd->argv, environ);
	cmd->pid = pid;
	return ;
}
