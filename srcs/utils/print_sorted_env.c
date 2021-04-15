#include "minishell.h"

#define FRONT 0
#define MID 1
#define END 2

static char	*get_str_literal(char *str)
{
	char	*ptr;
	char	*literal;

	ptr = ft_strchr(str, '=');
	if (ptr)
	{
		ptr = ft_strdup(ptr + 1);
		literal = ft_str_sandwich(ptr, "\"");
		free(ptr);
	}
	else
		literal = ft_strdup(str);
	return (literal);
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
		if (ft_strncmp(a[i], a[j], ft_strlen(a[i])) < 0)
			b[k++] = a[i++];
		else
			b[k++] = a[j++];
	}
	if (i == index[MID])
		while (j < index[END])
			b[k++] = a[j++];
	if (i != index[MID])
		while (i < index[MID])
			b[k++] = a[i++];
	i = 0;
	while (i < k)
	{
		a[index[FRONT] + i] = b[i];
		i++;
	}
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
	ft_memcpy(sorted, environ, sizeof(char *) * i);
	sorted[i] = NULL;
	sort_environ(sorted, buf, 0, i);
	free(buf);
	return (sorted);
}

int	print_sorted_env(void)
{
	char	**sorted;
	char	*value;
	size_t	i;

	sorted = get_sorted_environ();
	if (sorted == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (sorted[i] != NULL)
	{
		value = get_str_literal(sorted[i]);
		if (!value)
			return (EXIT_FAILURE);
		printf("declare -x ");
		while (*sorted[i] != '=')
			putchar(*sorted[i]++);
		putchar(*sorted[i]++);
		printf("%s\n", value);
		free(value);
		i++;
	}
	free(sorted);
	return (EXIT_SUCCESS);
}
