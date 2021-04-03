#include "minishell.h"

int		main(int argc, char **argv)
{
	t_command	*cmd;
	size_t		i;
	int			status;
	char		*key;
	char		*env;

	create_newenv();
	cmd = get_commandline(argv);
	status = execute_export(cmd);
	free_commandslist(&cmd);

	i = 1;
	while (i < argc)
	{
		key = ft_strchr(argv[i], '=');
		if (!key)
			key = ft_strdup(argv[i]);
		else
			key = ft_substr(argv[i], 0, key - argv[i]);
		env = getenv(key);
		if (env)
			printf("%s=%s\n", key, env);
		free(key);
		i++;
	}
	system("leaks test");
	return (status);
}
