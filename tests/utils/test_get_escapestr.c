#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*line;

	if (argc <= 1)
		return 0;
	line = get_escapestr(argv[1]);
	puts(line);
	free(line);
	return 0;
}