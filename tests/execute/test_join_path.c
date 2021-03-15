#include "minishell.h"

int main(void)
{
	char *cmd;
	char *path;

	cmd = ft_strdup("../minishell_git/srcs/../test../../testinout/test");
	path = join_path(cmd);
	puts(path);
	free(cmd);
	free(path);
	return 0;
}
