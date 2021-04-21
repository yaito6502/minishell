#include "minishell.h"

static void	make_newlist(char ***strs, char **new, int target_i)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*strs)[i] != NULL)
	{
		if (i == target_i)
		{
			free((*strs)[i]);
			i++;
			continue ;
		}
		new[j] = (*strs)[i];
		i++;
		j++;
	}
	new[j] = NULL;
}

bool	is_empty_env(char ***strs, char *line, int target_i)
{
	int		i;
	char	**new;

	if (*line != '\0')
		return (false);
	i = 0;
	while ((*strs)[i] != NULL)
		i++;
	new = malloc(sizeof(char *) * i);
	if (new == NULL)
		return (false);
	make_newlist(strs, new, target_i);
	free(*strs);
	free(line);
	*strs = new;
	return (true);
}
