#include "minishell.h"

int		main(int argc, char **argv)
{
	char		**token;
	char		*env;
	t_command	*cmd;
	int			status;

	create_newenv();
	cmd = get_commandline(argv);
	status = execute_cd(cmd);
	free_commandslist(&cmd);
	printf("status[%d]\n\n", status);

	token = tokenize("cd ../");
	cmd = get_commandline(token);
	status = execute_cd(cmd);
	ft_free_split(token);
	free_commandslist(&cmd);
	env = getenv("PWD");
	printf("PWD is %s\n", env);
	env = getenv("OLDPWD");
	printf("OLDPWD is %s\n", env);
	printf("status[%d]\n\n", status);

	token = tokenize("cd -");
	cmd = get_commandline(token);
	status = execute_cd(cmd);
	ft_free_split(token);
	free_commandslist(&cmd);
	env = getenv("PWD");
	printf("PWD is %s\n", env);
	env = getenv("OLDPWD");
	printf("OLDPWD is %s\n", env);
	printf("status[%d]\n\n", status);

	token = tokenize("cd -");
	cmd = get_commandline(token);
	status = execute_cd(cmd);
	ft_free_split(token);
	free_commandslist(&cmd);
	env = getenv("PWD");
	printf("PWD is %s\n", env);
	env = getenv("OLDPWD");
	printf("OLDPWD is %s\n", env);
	printf("status[%d]\n\n", status);

	token = tokenize("cd ~/Desktop");
	cmd = get_commandline(token);
	status = execute_cd(cmd);
	ft_free_split(token);
	free_commandslist(&cmd);
	env = getenv("PWD");
	printf("PWD is %s\n", env);
	env = getenv("OLDPWD");
	printf("OLDPWD is %s\n", env);
	printf("status[%d]\n\n", status);

	token = tokenize("cd ~Desktop");
	cmd = get_commandline(token);
	status = execute_cd(cmd);
	ft_free_split(token);
	free_commandslist(&cmd);
	env = getenv("PWD");
	printf("PWD is %s\n", env);
	env = getenv("OLDPWD");
	printf("OLDPWD is %s\n", env);
	printf("status[%d]\n\n", status);

	system("leaks test");
	return (0);

}
