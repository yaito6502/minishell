#include "minishell.h"

/*
** 標準入力のfdを保管(0)、復元(1)
*/

bool	reconnect_stdfd(int mode)
{
	static int stdfd[3];

	if (mode != 0 && mode != 1)
		return (false);
	if (mode == 0)
	{
		if ((stdfd[0] = dup(STDIN_FILENO)) == -1)
			return (false);
		if ((stdfd[1] = dup(STDOUT_FILENO)) == -1)
			return (false);
		if ((stdfd[2] = dup(STDERR_FILENO)) == -1)
			return (false);
		return (true);
	}
	if (dup2(stdfd[0], STDIN_FILENO) == -1)
		return (false);
	if (dup2(stdfd[1], STDOUT_FILENO) == -1)
		return (false);
	if (dup2(stdfd[2], STDERR_FILENO) == -1)
		return (false);
	return (true);
}
