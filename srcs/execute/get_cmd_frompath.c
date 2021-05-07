#include "minishell.h"

static char	**create_splitpath(void)
{
	extern char	**environ;
	char		**split_path;
	char		*tmp;
	int			i;

	i = 0;
	while (environ[i] != NULL && ft_strncmp(environ[i], "PATH", 4) != 0)
		i++;
	if (environ[i] == NULL)
		return (NULL);
	split_path = cut_eachcolon(environ[i]);
	if (split_path == NULL)
		return (NULL);
	tmp = split_path[0];
	split_path[0] = ft_substr(split_path[0], 5, ft_strlen(split_path[0]) - 5);
	free(tmp);
	if (split_path[0] == NULL)
		return (NULL);
	return (split_path);
}

static char	*join_cmd_and_path(char *dirpath, char *cmdname)
{
	char	*path;
	char	*tmp;

	path = ft_strjoin(dirpath, "/");
	if (path == NULL)
		return (NULL);
	tmp = path;
	path = ft_strjoin(path, cmdname);
	free(tmp);
	return (path);
}

#define CURRENTDIR "."

static char	*search_path(char **split_path, char *cmdname)
{
	DIR				*dir;
	struct dirent	*dp;
	char			*path;

	while (*split_path != NULL)
	{
		if ((*split_path)[0] != '\0')
			path = *split_path;
		else
			path = CURRENTDIR;
		dir = opendir(path);
		if (dir == NULL)
		{
			split_path++;
			continue ;
		}
		dp = readdir(dir);
		while (dp != NULL)
		{
			if (!ft_strncmp(dp->d_name, cmdname, ft_strlen(cmdname) + 1))
			{
				closedir(dir);
				return (join_cmd_and_path(path, cmdname));
			}
			dp = readdir(dir);
		}
		closedir(dir);
		split_path++;
	}
	return (NULL);
}

char	*get_cmd_frompath(t_command *cmd)
{
	char	**split_path;
	char	*fullpath;

	split_path = create_splitpath();
	if (!split_path)
		return (NULL);
	fullpath = NULL;
	if (split_path)
		fullpath = search_path(split_path, cmd->argv[0]);
	ft_free_split(split_path);
	return (fullpath);
}
