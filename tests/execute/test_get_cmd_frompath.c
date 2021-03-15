#include "minishell.h"

/*
** execveを実行するとメモリリークが追えないためコメントアウトしています。
*/

int main(void)
{
	extern char **environ;
	t_command cmd;
	char *path;
	cmd.argv = ft_split("ls,./",',');
	path = get_cmd_frompath(&cmd);
	printf("%s\n", path);
	free(path);
	ft_free_split(cmd.argv);
	//execve(path, cmd.argv, environ);
	return 0;
}