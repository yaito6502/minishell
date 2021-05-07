#include "minishell.h"

#define CURRENTDIR "."

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

static bool	check_executable(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		return (false);
	if (!(S_IXUSR & sb.st_mode))
		return (false);
	return (true);
}

static char	*search_dir(DIR *dir, char *path, char *cmdname)
{
	struct dirent	*dp;
	char			*filepath;

	dp = readdir(dir);
	while (dp != NULL)
	{
		if (!ft_strncmp(dp->d_name, cmdname, ft_strlen(cmdname) + 1))
		{
			filepath = join_cmd_and_path(path, cmdname);
			if (check_executable(filepath))
			{
				closedir(dir);
				return (filepath);
			}
			free(filepath);
		}
		dp = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}

static char	*search_path(char **split_path, char *cmdname)
{
	DIR		*dir;
	char	*tmp;
	char	*last_hit;

	last_hit = NULL;
	while (*split_path != NULL)
	{
		if ((*split_path)[0] != '\0')
			tmp = *split_path;
		else
			tmp = CURRENTDIR;
		dir = opendir(tmp);
		if (dir != NULL)
		{
			tmp = search_dir(dir, tmp, cmdname);
			if (tmp != NULL)
			{
				free(last_hit);
				last_hit = tmp;
			}
		}
		split_path++;
	}
	return (last_hit);
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
