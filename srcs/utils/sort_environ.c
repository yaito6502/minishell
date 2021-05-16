#include "minishell.h"

#define FRONT	0
#define MID		1
#define END		2

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
