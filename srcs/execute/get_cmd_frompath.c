#include "minishell.h"

static char	**create_splitpath(void)
{
	extern char	**environ;
	char		**split_path;
	char		*tmp;
	int			i;

	i = 0;
	while (ft_strncmp(environ[i], "PATH", 4) != 0)
		i++;
	split_path = ft_split(environ[i], ':');
	tmp = split_path[0];
	split_path[0] = ft_substr(split_path[0], 5, ft_strlen(split_path[0]) - 5);
	free(tmp);
	return (split_path);
}

static char	*search_path(char **split_path, char *cmdname)
{
	DIR				*dir;
	struct dirent	*dp;
	char			*path;
	char			*tmp;

	while (*split_path != NULL)
	{
		if ((dir = opendir(*split_path)) == NULL)
			continue ;
		while ((dp = readdir(dir)) != NULL)
			if (!ft_strncmp(dp->d_name, cmdname, ft_strlen(cmdname) + 1))
			{
				closedir(dir);
				path = ft_strjoin(*split_path, "/");
				tmp = path;
				path = ft_strjoin(path, cmdname);
				free(tmp);
				return (path);
			}
		closedir(dir);
		split_path++;
	}
	return (NULL);
}

/*
** env内PATHからcmdを検索する関数。pathの左が優先。
*/

char		*get_cmd_frompath(t_command *cmd)
{
	char	**split_path;
	char	*fullpath;

	split_path = create_splitpath();
	fullpath = search_path(split_path, cmd->argv[0]);
	ft_free_split(split_path);
	return (fullpath);
}
