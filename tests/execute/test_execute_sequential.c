#include "minishell.h"

//ゾンビプロセス確認
//ps aux | grep defunct | grep -v grep

int main(void)
{
	t_command	*cmd;
	int			status;
	extern char	**environ;

	cmd = create_new_tcommand();
	cmd->next = create_new_tcommand();
	cmd->next->next = create_new_tcommand();
	cmd->argv = ft_split("ls,./",',');
	cmd->next->argv = ft_split("cat,./testinout/infile1",',');
	cmd->next->next->argv = ft_split("cd,./srcs",',');

	while (cmd != NULL)
	{
		execute_sequential(cmd);
		printf("child pid : %d\n", cmd->pid);
		waitpid(cmd->pid, &status, 0);
		if (WIFEXITED(status))
			printf("child process ended successfully.\n");
		else
			printf("something wrong.\n");
		cmd = cmd->next;
	}

	//23 ~ 27 行目をコメントアウトして下3行をコメントイン、whileの位置をずらすことで、ゾンビプロセスの確認ができます。
	//while(1);
	//waitpid(0, &status, 0);
	//waitpid(0, &status, 0);
	free_commandslist(&cmd);
	return 0;
}
