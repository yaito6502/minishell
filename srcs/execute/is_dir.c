#include "minishell.h"

bool	is_dir(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		return (false);
	if (!S_ISDIR(sb.st_mode))
		return (false);
	return (true);
}
