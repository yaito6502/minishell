#include "minishell.h"

static bool	create_newenv(void)
{
	extern char	**environ;
	char		**new_env;
	int			i;
	size_t		size;

	i = 0;
	while (environ[i] != NULL)
		i++;
	size = (i + 1) * sizeof(char *);
	if (!(new_env = (char **)malloc(size)))
		return (false);
	ft_memcpy(new_env, environ, size);
	environ = new_env;
	return (true);
}

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

	return (0);
}