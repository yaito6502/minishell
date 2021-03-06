#include "minishell.h"

/*
** 標準入力のfdを保管(0)、復元(1)
*/

bool	reconnect_stdfd(int mode)
{
	static int	stdfd[3];
	int			i;
	int			ret;

	if (mode != SAVE && mode != LOAD)
		return (false);
	i = 0;
	while (i < 3 && mode == SAVE)
	{
		stdfd[i] = dup(i);
		if (stdfd[i] == -1)
			return (false);
		i++;
	}
	while (i < 3 && mode == LOAD)
	{
		ret = dup2(stdfd[i], i);
		if (ret == -1)
			return (false);
		i++;
	}
	return (true);
}
