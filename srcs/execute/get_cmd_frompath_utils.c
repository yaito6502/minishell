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
	printf("%d\n", n);
	return (n);
}

char	**cut_eachcolon(char *path)
{
	char	**split_path;
	int		n;
	int		i;
	char	*tmp;
	size_t	size;

	n = getlen(path);
	split_path = (char **)malloc(sizeof(char *) * (n + 1));
	if (split_path == NULL)
		return (error_malloc());
	split_path[n] = NULL;
	i = 0;
	while (i < n)
	{
		tmp = ft_strchr(path, ':');
		if (tmp == NULL)
			tmp = ft_strchr(path, '\0');
		size = (size_t)(tmp - path);
		split_path[i] = ft_substr(path, 0, size);
		if (split_path[i] == NULL)
			return (error_malloc());
		path = tmp + 1;
		i++;
	}
	return (split_path);
}