#include "minishell.h"

/*
**exitで終了ステータスを呼び出し元に返す。
**成功時 0
**失敗時 1
*/

int	execute_pwd(t_command *cmd)
{
	char	*path;

	(void)cmd;
	path = getenv("PWD");
	if (path == NULL)
		return (EXIT_FAILURE);
	printf("%s\n", path);
	return (EXIT_SUCCESS);
}
