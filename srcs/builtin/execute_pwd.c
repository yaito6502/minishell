#include "minishell.h"

/*
**exitで終了ステータスを呼び出し元に返す。
**成功時 0
**失敗時 エラー番号(>0)
*/

void	execute_pwd(t_command *cmd)
{
	char *path;

	path = getenv("PWD");
	if (path == NULL)
		exit(errno);
	printf("%s\n", path);
	exit(EXIT_SUCCESS);
}
