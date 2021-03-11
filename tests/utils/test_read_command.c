#include "minishell.h"

int		main(void)
{
	char *line;

	line = read_command();
	printf("%s", line);
	free(line);
	return (0);
}
