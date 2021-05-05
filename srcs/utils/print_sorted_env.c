#include "minishell.h"

#define FRONT 0
#define MID 1
#define END 2

static bool	get_str_literal(char *str, char **literal)
{
	char	*ptr;

	*literal = NULL;
	ptr = ft_strchr(str, '=');
	if (!ptr)
		return (false);
	ptr = ft_str_sandwich(ptr + 1, "\"");
	*literal = ft_strjoin("=", ptr);
	free(ptr);
	return (true);
}

static void	merge(char **a, char **b, size_t index[3])
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = index[FRONT];
	j = index[MID];
	k = 0;
	while (i < index[MID] && j < index[END])
	{
		if (ft_strncmp(a[i], a[j], INT_MAX) < 0)
			b[k++] = a[i++];
		else
			b[k++] = a[j++];
	}
	if (i == index[MID])
		while (j < index[END])
			b[k++] = a[j++];
	else
		while (i < index[MID])
			b[k++] = a[i++];
	i = k;
	while (i--)
		a[index[FRONT] + i] = b[i];
}

void	sort_environ(char **a, char **b, size_t front, size_t end)
{
	size_t	mid;
	size_t	index[3];

	if (front == end || front + 1 == end)
		return ;
	mid = (front + end) / 2;
	sort_environ(a, b, front, mid);
	sort_environ(a, b, mid, end);
	index[0] = front;
	index[1] = mid;
	index[2] = end;
	merge(a, b, index);
}

char	**get_sorted_environ(void)
{
	extern char	**environ;
	char		**sorted;
	char		**buf;
	size_t		i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	sorted = (char **)malloc(sizeof(char *) * (i + 1));
	buf = (char **)malloc(sizeof(char *) * (i + 1));
	if (!sorted || !buf)
	{
		free(sorted);
		free(buf);
		return (NULL);
	}
	ft_memcpy(sorted, environ, sizeof(char *) * (i + 1));
	sorted[i] = NULL;
	sort_environ(sorted, buf, 0, i);
	free(buf);
	return (sorted);
}

int	print_sorted_env(void)
{
	char	**sorted;
	char	*value;
	bool	has_value;
	size_t	i;

	sorted = get_sorted_environ();
	if (sorted == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (sorted[i] != NULL)
	{
		has_value = get_str_literal(sorted[i], &value);
		if (has_value && !value)
			return (EXIT_FAILURE);
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		while (*sorted[i] && *sorted[i] != '=')
			ft_putchar(*sorted[i]++);
		if (has_value)
			ft_putstr_fd(value, STDOUT_FILENO);
		free(value);
		ft_putendl_fd("", STDOUT_FILENO);
		i++;
	}
	free(sorted);
	return (EXIT_SUCCESS);
}
