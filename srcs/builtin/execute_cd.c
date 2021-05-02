#include "minishell.h"

static char	*retry_change_directory(char *path)
{
	char	*newpath;
	char	*tmp;
	char	*pwd;

	if (chdir(path) == -1)
		return (NULL);
	pwd = getenv("PWD");
	tmp = pwd;
	if (!endswith(pwd, "/"))
		tmp = ft_strjoin(pwd, "/");
	newpath = ft_strjoin(tmp, path);
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
	size_t	i;

	split_path = ft_split(getenv("CDPATH"), ':');
	if (split_path == NULL)
		return (false);
	i = 0;
	while (split_path[i] != NULL)
	{
		if (!endswith(split_path[i], "/"))
			split_path[i] = add_path(split_path[i], NULL);
		newpath = ft_strjoin(split_path[i], path);
		if (change_directory(newpath, true) == 0)
		{
			free(newpath);
			ft_free_split(split_path);
			return (true);
		}
		free(newpath);
		i++;
	}
	ft_free_split(split_path);
	return (false);
}

static char	*select_path(char *str)
{
	char	*path;

	path = str;
	if (getenv("HOME") == NULL && path == NULL)
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
	else if (path == NULL || *path == '~')
		path = expand_firsttilde(path);
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
	if (!ft_strchr(path, '/') && !ft_strchr(path, '.') && set_cdpath_iterate(path))
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
