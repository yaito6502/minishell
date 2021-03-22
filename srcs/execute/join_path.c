#include "minishell.h"

char	*get_cwd_with_slash(void)
{
	char *path;
	char *tmp;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (NULL);
	tmp = path;
	path = ft_strjoin(path, "/");
	if (path == NULL)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (path);
}

char	*add_dir_topath(char *path, char *buf)
{
	char *tmp;

	tmp = path;
	path = ft_strjoin(path, buf);
	if (path == NULL)
		return (NULL);
	free(tmp);
	return (path);
}

char	*check_buf(char *path, char *buf)
{
	char *tmp;

	if (!ft_strncmp(buf, "./", 2))
		return (path);
	if (!ft_strncmp(buf, "../", 3))
	{
		tmp = path;
		while (*path)
			path++;
		path = path - 2;
		while (*path != '/')
			path--;
		path[1] = '\0';
		path = tmp;
		return (path);
	}
	path = add_dir_topath(path, buf);
	if (path == NULL)
		return (NULL);
	return (path);
}

char	*read_path(char *cmd, char *buf)
{
	int		len;
	char	tmp[2048];

	len = 0;
	while (cmd[len] != '/' && cmd[len] != '\0')
		len++;
	ft_strlcpy(tmp, cmd, len + 1);
	if (cmd[len] == '/')
	{
		tmp[len] = '/';
		tmp[len + 1] = '\0';
	}
	free(buf);
	buf = ft_strdup(tmp);
	if (buf == NULL)
		return (NULL);
	return (buf);
}

/*
** cmd->argv[0]内にスラッシュが含まれる場合、ワーキングディレクトリから絶対パスを生成する。
** cwdにスラッシュまでを足す。./無視。../が来たときは一個削る。
*/

char	*join_path(char *cmd)
{
	char	*path;
	char	*buf;

	if (*cmd == '/')
		return (cmd);
	buf = NULL;
	path = get_cwd_with_slash();
	if (path == NULL)
		return (NULL);
	while (*cmd != '\0')
	{
		buf = read_path(cmd, buf);
		if (buf == NULL)
			return (NULL);
		cmd = cmd + ft_strlen(buf);
		path = check_buf(path, buf);
		if (path == NULL)
			return (NULL);
	}
	free(buf);
	return (path);
}
