#include "minishell.h"

static void	*error_malloc(void)
{
	ft_putstr_fd("minishell: malloc: ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	return (NULL);
}

static int	getlen(char *path)
{
	int	n;
	int	i;

	i = 0;
	n = 1;
	while (path[i] != '\0')
	{
		if (path[i] == ':')
			n++;
		i++;
	}
	return (n);
}

static char	*get_split_path(char **path)
{
	char	*tmp;
	char	*split_path;
	size_t	size;

	tmp = ft_strchr(*path, ':');
	if (tmp == NULL)
		tmp = ft_strchr(*path, '\0');
	size = tmp - *path;
	if (size == 0)
		split_path = ft_strdup(".");
	else
		split_path = ft_substr(*path, 0, size);
	*path = tmp + 1;
	return (split_path);
}

char	**cut_eachcolon(char *path)
{
	char	**split_path;
	int		n;
	int		i;

	if (!path)
		return (NULL);
	n = getlen(path);
	split_path = (char **)malloc(sizeof(char *) * (n + 1));
	if (split_path == NULL)
		return (error_malloc());
	split_path[n] = NULL;
	i = 0;
	while (i < n)
	{
		split_path[i] = get_split_path(&path);
		if (split_path[i] == NULL)
			return (error_malloc());
		i++;
	}
	return (split_path);
}
