#include "minishell.h"

//末尾5メンバのみ出力
static void	print_env()
{
	int			i;
	int			num;
	extern char	**environ;

	num = 0;
	while (environ[num])
		num++;
	i = num - 5;
	while(i < num)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return ;
}

int			main(void)
{
	extern char	**environ;

	print_env();
	create_newenv();
	add_newval_to_env("test is success!");
	add_newval_to_env("second test is success!");
	print_env();
	ft_free_split(environ);
	return (0);
}