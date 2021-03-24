#include "minishell.h"

/*
**exitで終了ステータスを呼び出し元に返す。
*/

void	execute_pwd(t_command *cmd)
{
	char *path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		exit(errno);
	printf("%s\n", path);
	free(path);
	exit(EXIT_SUCCESS);
}
