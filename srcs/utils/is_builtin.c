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


// int		main(void)
// {
// 	t_command test;

// 	test.argv = malloc(sizeof(char**) * 2);
// 	test.argv[1] = NULL;
// 	test.argv[0] = ft_strdup("echo");
// 	printf("%d\n", is_builtin(&test));
// 	test.argv[0] = ft_strdup("cd");
// 	printf("%d\n", is_builtin(&test));
// 	test.argv[0] = ft_strdup("pwd");
// 	printf("%d\n", is_builtin(&test));
// 	test.argv[0] = ft_strdup("export");
// 	printf("%d\n", is_builtin(&test));
// 	test.argv[0] = ft_strdup("unset");
// 	printf("%d\n", is_builtin(&test));
// 	test.argv[0] = ft_strdup("env");
// 	printf("%d\n", is_builtin(&test));
// 	test.argv[0] = ft_strdup("exit");
// 	printf("%d\n", is_builtin(&test));
// 	test.argv[0] = ft_strdup("invalid");
// 	printf("%d\n", is_builtin(&test));
// 	test.argv[0] = ft_strdup("exportaaa");
// 	printf("%d\n", is_builtin(&test));
// 	return (0);
// }
