#include "minishell.h"

/*
** execveを実行するとメモリリークが追えないためコメントアウトしています。
*/

int main(int argc, char **argv)
{
	char **tokens;
	t_command *cmd;
	char *path;

	(void)argc;
	tokens = tokenize(argv[1]);
	cmd = parse(tokens);
	puts(cmd->argv[0]);
	path = get_cmd_frompath(cmd);
	if (path != NULL)
		printf("%s\n", path);
	else
		puts("NULL");
	free(path);
	ft_free_split(tokens);
	free_commandslist(&cmd);
	//execve(path, cmd.argv, environ);
	return 0;
}