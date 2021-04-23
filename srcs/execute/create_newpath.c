#include "minishell.h"

static char	*get_cwd_with_slash(void)
{
	char	*path;
	char	*tmp;

	path = getcwd(NULL, 0);
	if (!path)
		return (NULL);
	tmp = path;
	path = ft_strjoin(path, "/");
	if (!path)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (path);
}

static char	**get_dir_separeted_by_slash(char *path)
{
	char	*cwd;
	char	*newpath;
	char	**dir;

	if (*path == '/')
		return (ft_split(path, '/'));
	cwd = get_cwd_with_slash();
	if (!cwd)
		return (NULL);
	newpath = ft_strjoin(cwd, path);
	free(cwd);
	if (!newpath)
		return (NULL);
	dir = ft_split(newpath, '/');
	free(newpath);
	return (dir);
}

static bool	is_validdir(char *dir)
{
	struct stat	sb;

	if (lstat(dir, &sb) == -1)
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

static t_list	*create_hierarchy(char *path)
{
	char	**dir;
	t_list	*last;
	t_list	*list;

	dir = get_dir_separeted_by_slash(path);
	list = NULL;
	ft_lstadd_back(&list, ft_lstnew(ft_strdup(NULL)));
	while (dir && *dir != NULL)
	{
		if (!ft_strncmp(*dir, "..", 3))
		{
			last = list;
			if (last)
			{
				while (last->next && last->next->next)
					last = last->next;
				ft_lstdelone(last->next, free);
				last->next = NULL;
			}
		}
		else if (ft_strncmp(*dir, ".", 2))
			ft_lstadd_back(&list, ft_lstnew(*dir));
		dir++;
	}
	return (list);
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

char	*create_newpath(char *path)
{
	char	*newpath;
	t_list	*head;
	t_list	*list;

	if (!ft_strncmp(path, "/", 2))
		return (ft_strdup(path));
	list = create_hierarchy(path);
	head = list;
	newpath = NULL;
	if (list && list->next)
		list = list->next;
	while (list != NULL)
	{
		newpath = add_path(newpath, list->content);
		if (!is_validdir(newpath))
		{
			free(newpath);
			newpath = NULL;
		}
		if (!newpath)
			break ;
		list = list->next;
	}
	ft_lstclear(&head, free);
	return (newpath);
}
