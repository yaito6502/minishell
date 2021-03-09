#include <minishell.h>

bool	is_builtin(t_command *cmds)
{
	int			i;
	const char	builtin_list[][7] = {
		{"echo"},
		{"cd"},
		{"pwd"},
		{"export"},
		{"unset"},
		{"env"},
		{"exit"},
		NULL};

	i = 0;
	while (builtin_list[i] != NULL)
	{
		if (!ft_strcmp(cmds->argv[0], builtin_list[i]))
			return (true);
	}
	return (false);
}