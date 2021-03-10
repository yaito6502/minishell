#include <minishell.h>

/*
** t_command内、argv[0]を各ビルトインコマンドと比較、該当する場合、indexを返す。ない場合は、-1を返す。
*/

int		is_builtin(t_command *cmds)
{
	int			i;
	const char	builtin_list[][7] = {
		{"echo"},
		{"cd"},
		{"pwd"},
		{"export"},
		{"unset"},
		{"env"},
		{"exit"}};

	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(cmds->argv[0], builtin_list[i], 7))
			return (i);
		i++;
	}
	return (-1);
}
