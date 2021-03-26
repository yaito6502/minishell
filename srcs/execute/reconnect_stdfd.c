#include "minishell.h"

/*
** 標準入力のfdを保管(0)、復元(1)
*/

bool	reconnect_stdfd(int mode)
{
	static int	stdfd[3];
	int			i;
	int			ret;

	if (mode != 0 && mode != 1)
		return (false);
	i = 0;
	if (mode == 0)
	{
		while (i < 3)
		{
			stdfd[i] = dup(i);
			if (stdfd[i] == -1)
				return (false);
			i++;
		}
		return (true);
	}
	while (i < 3)
	{
		ret = dup2(stdfd[i], i);
		if (ret == -1)
			return (false);
		i++;
	}
	return (true);
}
