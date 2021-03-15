#include "minishell.h"

/*
** argv[0]内に/があるか確認する。あったらtrue、なかったらfalseを返す。
*/

bool	has_slash(char *cmd)
{
	while(*cmd != '/')
	{
		cmd++;
		if (*cmd == '\0')
			return (false);
	}
	return (true);
}