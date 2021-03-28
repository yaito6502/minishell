#include "minishell.h"

int		print_error(char *message)
{
	message = ft_strjoin("minishell: cd: ", message);
	if (message == NULL)
		printf("%s\n", strerror(errno));
	else
		printf("%s\n", message);
	return (EXIT_FAILURE);
}

int		set_path(char *path)
{
	int			status;
	char		*pwd;
	//t_command	*cmd;

	printf("path[%s]\n", join_path(path)); //デバッグ用
	status = chdir(join_path(path));
	if (status == -1)
		return (print_error(ft_strjoin(path, ": No such file or directory")));
	pwd = getenv("PWD");
	if (pwd == NULL)
		return (EXIT_FAILURE);
	/*create_newenv();
	cmd = create_new_tcommand();
	cmd->argv = (char **)malloc(sizeof(char *) * 2);
	cmd->argv[0] = ft_strdup("OLDPWD");
	cmd->argv[1] = NULL;
	execute_unset(cmd);
	free_commandslist(&cmd);*/
	status = add_newval_to_env(ft_strjoin("OLDPWD=", pwd));
	if (status == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

bool	cdpath(char *path)
{
	char	*newpath;
	char	**split_path;
	int		status;

	split_path = ft_split(getenv("CDPATH"), ':');
	if (split_path == NULL)
		return (false);
	while (*split_path != NULL)
	{
		if (set_path(ft_strjoin(*split_path, path)) == 0)
			return (true);
		split_path++;
	}
	return (false);
}

/*
**　pathの指定がない場合、環境変数HOMEへ移動
**　HOMEが設定されていない場合エラーを返す
**　cd - の場合
*/
int		execute_cd(t_command *cmd)
{
	char		*path;
	int			status;

	if (!cmd)
		return (EXIT_FAILURE);
	path = cmd->argv[1];
	if (path == NULL)
	{
		path = getenv("HOME");
		if (path == NULL)
			return (print_error("HOME not set"));
	}
	else if (!ft_strncmp(path, "-", 2))
	{
		path = getenv("OLDPWD");
		if (path == NULL)
			return (print_error("OLDPWD not set"));
		printf("%s\n", path);
	}
	else if (ft_strncmp(path, "/", 1))
		if (cdpath(path))
			return (EXIT_SUCCESS);
	return (set_path(path));
}
