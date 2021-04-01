#include "minishell.h"

int		main(int argc, char **argv)
{
	char		*env;
	t_command	*cmd;
	int			status;

	create_newenv();
	cmd = get_commandline(argv);
	status = execute_cd(cmd);
	free_commandslist(&cmd);
	printf("status[%d]\n\n", status);

	cmd = get_commandline(tokenize("cd ../"));
	status = execute_cd(cmd);
	free_commandslist(&cmd);
	env = getenv("PWD");
	printf("PWD is %s\n", env);
	env = getenv("OLDPWD");
	printf("OLDPWD is %s\n", env);
	printf("status[%d]\n\n", status);

	cmd = get_commandline(tokenize("cd -"));
	status = execute_cd(cmd);
	free_commandslist(&cmd);
	env = getenv("PWD");
	printf("PWD is %s\n", env);
	env = getenv("OLDPWD");
	printf("OLDPWD is %s\n", env);
	printf("status[%d]\n\n", status);

	cmd = get_commandline(tokenize("cd -"));
	status = execute_cd(cmd);
	free_commandslist(&cmd);
	env = getenv("PWD");
	printf("PWD is %s\n", env);
	env = getenv("OLDPWD");
	printf("OLDPWD is %s\n", env);
	printf("status[%d]\n\n", status);

	cmd = get_commandline(tokenize("cd ~/Desktop"));
	status = execute_cd(cmd);
	free_commandslist(&cmd);
	env = getenv("PWD");
	printf("PWD is %s\n", env);
	env = getenv("OLDPWD");
	printf("OLDPWD is %s\n", env);
	printf("status[%d]\n\n", status);

	cmd = get_commandline(tokenize("cd ~Desktop"));
	status = execute_cd(cmd);
	free_commandslist(&cmd);
	env = getenv("PWD");
	printf("PWD is %s\n", env);
	env = getenv("OLDPWD");
	printf("OLDPWD is %s\n", env);
	printf("status[%d]\n\n", status);

	return (0);

}
