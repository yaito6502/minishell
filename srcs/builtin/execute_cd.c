#include "minishell.h"

static int	print_error(char *message)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	return (EXIT_FAILURE);
}

static int	set_path(char *path)
{
	char		*newpath;
	int			ret;

	if (!path)
		return (EXIT_FAILURE);
	newpath = join_path(path);
	if (chdir(newpath) == -1)
	{
		free(newpath);
		print_error(path);
		ft_putendl_fd(":No such file or directory", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ret = (!update_env("OLDPWD", getenv("PWD"))
			|| !update_env("PWD", newpath));
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
		newpath = ft_strjoin(split_path[i], path);
		if (set_path(newpath) == 0)
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

static char	*expand_tilde(char *path)
{
	char	*home;
	char	*expd_path;

	if (path && path[1] != '\0' && path[1] != '/')
	{
		print_error(path);
		ft_putendl_fd(":No such file or directory", STDERR_FILENO);
		return (NULL);
	}
	home = getenv("HOME");
	if (home == NULL)
	{
		print_error("HOME not set\n");
		return (NULL);
	}
	if (path)
		expd_path = ft_strjoin(home, path + 1);
	else
		expd_path = ft_strdup(home);
	if (expd_path == NULL)
		print_error(strerror(errno));
	return (expd_path);
}

int	execute_cd(t_command *cmd)
{
	char		*path;
	int			status;

	path = cmd->argv[1];
	if (path == NULL || *path == '~')
		path = expand_tilde(path);
	else if (!ft_strncmp(path, "-", 2))
	{
		path = ft_strdup(getenv("OLDPWD"));
		if (path == NULL)
			return (print_error("OLDPWD not set\n"));
		ft_putendl_fd(path, STDOUT_FILENO);
	}
	else
	{
		if (ft_strncmp(path, "/", 1) && set_cdpath_iterate(path))
			return (EXIT_SUCCESS);
		path = ft_strdup(path);
	}
	status = set_path(path);
	free(path);
	return (status);
}
