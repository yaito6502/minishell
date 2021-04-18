#include "minishell.h"

/*
** $12USERのとき$12までがkeyとして認識される。
*/

void	get_envname(char *line, int *i)
{
	if(ft_isdigit(line[*i]))
	{
		while(ft_isdigit(line[*i]))
			(*i)++;
		return ;
	}
	while (ft_isalnum(line[*i]) || line[*i] == '_')
		(*i)++;
	return ;
}
