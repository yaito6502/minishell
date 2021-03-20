#include "minishell.h"

int		main(void)
{
	char *line;

	line = read_command();
	printf("%s\n", line);
	free(line);
	system("leaks test");
	return (0);
}
