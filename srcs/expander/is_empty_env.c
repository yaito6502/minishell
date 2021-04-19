#include "minishell.h"

bool	is_empty_env(char ***strs, char *line, int target_i)
{
	int		i;
	int		j;
	char	**new;

	if (*line != '\0')
		return (false);
	i = 0;
	while((*strs)[i] != NULL)
		i++;
	new = malloc(sizeof(char *) * i);
	if (new == NULL)
		return (false);
	i = 0;
	j = 0;
	while ((*strs)[i] != NULL)
	{
		if (i == target_i)
		{
			free((*strs)[i]);
			i++;
			target_i = -1;
			continue ;
		}
		new[j] = (*strs)[i];
		i++;
		j++;
	}
	new[j] = NULL;
	free(*strs);
	*strs = new;
	return (true);
}
