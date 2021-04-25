#include "minishell.h"

char	*create_newpath(char *path);

int		main(int argc, char **argv)
{
	char *path;

	if (argc != 2)
		return (1);
	path = create_newpath(argv[1]);
	puts(path);
	return (0);
}
