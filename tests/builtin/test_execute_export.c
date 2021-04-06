#include "minishell.h"

int		main(int argc, char **argv)
{
	t_command	*cmd;
	size_t		i;
	int			status;
	char		*key;
	char		*env;

	create_newenv();
	//cmd = get_commandline(argv);
	cmd = create_new_tcommand();
	cmd->argv = ft_split(argv[1], ',');
	status = execute_export(cmd);

	i = 1;
	while (cmd->argv[i] != NULL)
	{
		key = ft_strchr(cmd->argv[i], '=');
		if (!key)
			key = ft_strdup(cmd->argv[i]);
		else
			key = ft_substr(cmd->argv[i], 0, key - cmd->argv[i]);
		env = getenv(key);
		if (env)
			printf("%s=%s\n", key, env);
		free(key);
		i++;
	}
	free_commandslist(&cmd);
	system("leaks test");
	return (status);
}
