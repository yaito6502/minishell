#include "minishell.h"

/*
** keyが環境変数として適切か判定する。
** 始まりはアルファベット、アルファベットと数字、アンダースコアのスネークケース
*/

bool	validate_envkey(char *key)
{
	if (key == NULL)
		return (false);
	if (*key == '\0')
		return (false);
	if (!ft_isalpha(*key) && *key != '_')
		return (false);
	key++;
	while (*key != '\0')
	{
		if (!(ft_isalnum(*key) || *key == '_'))
			return (false);
		key++;
	}
	return (true);
}
