#include "minishell.h"

#define CURRENTDIR "."

//static char	**create_splitpath(void)
//{
//	char		**split_path;
//	char		*tmp;
//
//	split_path = cut_eachcolon(getenv("PATH"));
//	if (split_path == NULL)
//		return (NULL);
//	tmp = split_path[0];
//	split_path[0] = ft_substr(split_path[0], 5, ft_strlen(split_path[0]) - 5);
//	free(tmp);
//	if (split_path[0] == NULL)
//		return (NULL);
//	return (split_path);
//}
//
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

static char	*check_dir(DIR *dir, char *path, char *cmdname)
{
	struct dirent	*dp;

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
	return (NULL);
}

static char	*search_path(char **split_path, char *cmdname)
{
	DIR		*dir;
	char	*path;
	char	*ret;

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
		ret = check_dir(dir, path, cmdname);
		if (ret != NULL)
			return (ret);
		split_path++;
	}
	return (NULL);
}

char	*get_cmd_frompath(t_command *cmd)
{
	char	**split_path;
	char	*fullpath;

	split_path = cut_eachcolon(getenv("PATH"));
	if (!split_path)
		return (NULL);
	fullpath = NULL;
	if (split_path)
		fullpath = search_path(split_path, cmd->argv[0]);
	ft_free_split(split_path);
	return (fullpath);
}
