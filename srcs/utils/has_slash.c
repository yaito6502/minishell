#include "minishell.h"

/*
** argv[0]内に/があるか確認する。あったらtrue、なかったらfalseを返す。
*/

bool	has_slash(char *str)
{
	if (ft_strchr(str, '/') == NULL)
		return (false);
	return (true);
}