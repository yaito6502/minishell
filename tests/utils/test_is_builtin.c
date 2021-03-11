#include "minishell.h"

int		main(void)
{
	t_command test;

	test.argv = malloc(sizeof(char**) * 2);
	test.argv[1] = NULL;
	test.argv[0] = ft_strdup("echo");
	printf("%d\n", is_builtin(&test));
	test.argv[0] = ft_strdup("cd");
	printf("%d\n", is_builtin(&test));
	test.argv[0] = ft_strdup("pwd");
	printf("%d\n", is_builtin(&test));
	test.argv[0] = ft_strdup("export");
	printf("%d\n", is_builtin(&test));
	test.argv[0] = ft_strdup("unset");
	printf("%d\n", is_builtin(&test));
	test.argv[0] = ft_strdup("env");
	printf("%d\n", is_builtin(&test));
	test.argv[0] = ft_strdup("exit");
	printf("%d\n", is_builtin(&test));
	test.argv[0] = ft_strdup("invalid");
	printf("%d\n", is_builtin(&test));
	test.argv[0] = ft_strdup("exportaaa");
	printf("%d\n", is_builtin(&test));
	return (0);
}
