#include "minishell.h"

static int	print_error(char *message)
{
	printf("minishell: cd: ");
	printf("%s", message);
	return (EXIT_FAILURE);
}

static bool	update_env(char *key, char *value)
{
	extern char	**environ;
	char		*env;
	size_t		i;
	bool		status;

	if (!key || !value) //validate_envkeyを追加する
		return (false);
	env = ft_strjoin(key, value);
	if (env == NULL)
		return (false);
	i = 0;
	while (environ[i] != NULL && ft_strncmp(environ[i], key, ft_strlen(key)))
		i++;
	status = true;
	if (environ[i] == NULL)
		status = add_newval_to_env(env);
	(environ[i] == NULL ? free(env) : free(environ[i]));
	if (environ[i] != NULL)
		environ[i] = env;
	return (status);
}

static int	set_path(char *path)
{
	char		*newpath;

	newpath = join_path(path);
	if (chdir(newpath) == -1)
	{
		print_error(path);
		printf("%s\n", ":No such file or directory");
		return (EXIT_FAILURE);
	}
	if (!update_env("OLDPWD=", getenv("PWD")) || !update_env("PWD=", path))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static bool	set_cdpath_iterate(char *path)
{
	char	*newpath;
	char	**split_path;

	split_path = ft_split(getenv("CDPATH"), ':');
	if (split_path == NULL)
		return (false);
	while (*split_path != NULL)
	{
		newpath = ft_strjoin(*split_path, path);
		if (set_path(newpath) == 0)
		{
			free(newpath);
			ft_free_split(split_path);
			return (true);
		}
		free(newpath);
		split_path++;
	}
	ft_free_split(split_path);
	return (false);
}

/*
**　normの行数オーバーは未解決
**　getenvはmallocを伴わないのか、freeするとエラーが起きる。
*/

int		execute_cd(t_command *cmd)
{
	char		*path;
	int			status;

	path = cmd->argv[1];
	if (path == NULL || *path == '~')
	{
		path = getenv("HOME");
		if (path == NULL)
			return (print_error("HOME not set\n"));
		if (cmd->argv[1])
		{
			path = ft_strjoin(path, cmd->argv[1] + 1);
			status = set_path(path);
			free(path);
			return (status);
		}
	}
	else if (!ft_strncmp(path, "-", 2))
	{
		path = getenv("OLDPWD");
		if (path == NULL)
			return (print_error("OLDPWD not set\n"));
		printf("%s\n", path);
	}
	else if (ft_strncmp(path, "/", 1) && set_cdpath_iterate(path))
		return (EXIT_SUCCESS);
	return (set_path(path));
}
