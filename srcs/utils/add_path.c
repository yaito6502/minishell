#include "minishell.h"

static bool	is_validdir(char *dir)
{
	struct stat	sb;

	if (stat(dir, &sb) == -1)
		return (false);
	if (!S_ISDIR(sb.st_mode))
	{
		errno = ENOTDIR;
		return (false);
	}
	if (!(S_IXUSR & sb.st_mode))
	{
		errno = EACCES;
		return (false);
	}
	return (true);
}

char	*add_path_iterate(t_list *list)
{
	char	*newpath;

	newpath = NULL;
	while (list != NULL)
	{
		newpath = add_path(newpath, list->content);
		if (!is_validdir(newpath))
		{
			free(newpath);
			newpath = NULL;
		}
		if (!newpath)
			return (NULL);
		list = list->next;
	}
	return (newpath);
}

char	*add_path(char *path, char *dir)
{
	char	*newpath;
	char	*oldpath;

	newpath = ft_strjoin(path, "/");
	if (!newpath)
		return (NULL);
	oldpath = newpath;
	newpath = ft_strjoin(oldpath, dir);
	free(oldpath);
	return (newpath);
}
