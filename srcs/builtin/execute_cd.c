#include "minishell.h"

#define ERR_GETCWD "cd: error retrieving current directory: getcwd:\
 cannot access parent directories: No such file or directory"

char	*retry_change_directory(char *path)
{
	char	*newpath;
	char	*try;
	char	*pwd;

	if (chdir(path) == -1)
		return (NULL);
	pwd = getenv("PWD");
	if (!endswith(pwd, "/"))
		pwd = ft_strjoin(pwd, "/");
	else
		pwd = ft_strdup(pwd);
	try = ft_strjoin(pwd, path);
	free(pwd);
	newpath = create_newpath(try);
	if (!newpath && store_exitstatus(LOAD, errno) == ENOENT)
	{
		ft_putendl_fd(ERR_GETCWD, STDERR_FILENO);
		return (try);
	}
	free(try);
	return (newpath);
}

static int	change_directory(char *path, bool is_putpath)
{
	char		*newpath;
	int			ret;

	if (!path)
		return (EXIT_SUCCESS);
	newpath = create_newpath(path);
	store_exitstatus(SAVE, errno);
	if (chdir(newpath) == -1)
	{
		free(newpath);
		newpath = retry_change_directory(path);
		if (!newpath)
			return (EXIT_FAILURE);
	}
	ret = (!update_env("OLDPWD", getenv("PWD"))
			|| !update_env("PWD", newpath));
	if (is_putpath)
		ft_putendl_fd(newpath, STDOUT_FILENO);
	free(newpath);
	if (ret == true)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static bool	set_cdpath_iterate(char *path)
{
	char	*newpath;
	char	**split_path;
	bool	is_success;
	bool	is_putpath;
	size_t	i;

	if (path[0] == '\0' || ft_strchr(path, '.') || ft_strchr(path, '/'))
		return (false);
	split_path = cut_eachcolon(getenv("CDPATH"));
	i = 0;
	is_success = false;
	while (!is_success && split_path && split_path[i] != NULL)
	{
		is_putpath = ft_strncmp(split_path[i], ".", 2);
		if (!endswith(split_path[i], "/"))
			split_path[i] = add_path(split_path[i], NULL);
		newpath = ft_strjoin(split_path[i], path);
		if (change_directory(newpath, is_putpath) == 0)
			is_success = true;
		free(newpath);
		i++;
	}
	ft_free_split(split_path);
	return (is_success);
}

static char	*select_path(char *str)
{
	char	*path;

	path = str;
	if (!path)
	{
		path = ft_strdup(getenv("HOME"));
		if (!path)
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
	}
	else if (!ft_strncmp(path, "-", 2))
	{
		path = ft_strdup(getenv("OLDPWD"));
		if (path)
			ft_putendl_fd(path, STDOUT_FILENO);
		else
			ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
	}
	else
		path = ft_strdup(path);
	return (path);
}

int	execute_cd(t_command *cmd)
{
	char		*path;
	int			status;

	path = select_path(cmd->argv[1]);
	if (!path)
		return (EXIT_FAILURE);
	if (set_cdpath_iterate(path))
		return (EXIT_SUCCESS);
	status = change_directory(path, false);
	if (status)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(store_exitstatus(LOAD, errno)), STDERR_FILENO);
	}
	free(path);
	return (status);
}
