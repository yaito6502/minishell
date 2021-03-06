#include "minishell.h"

static void print_env()
{
	int			i;
	extern char	**environ;
	i = 0;
	while (environ[i])
		i++;
	printf("current env num is %d.\n", i);
	i = 0;
	while(i < 10)
	{
		puts(environ[i]);
		i++;
	}
	return ;
}

int main(void)
{
	int			i;
	int			ret;
	t_command	*cmd;
	extern char	**environ;

	create_newenv();
	print_env();
	puts("-------------");
	cmd = create_new_tcommand();
	cmd->argv = ft_split("unset,\"\",\"\",INVALID",',');
	preprocess_command(cmd);
	ret = execute_unset(cmd);
	printf("%d\n", ret);
	print_env();
	ft_free_split(environ);
	ft_free_split(cmd->argv);
	free(cmd);
	return 0;
}
