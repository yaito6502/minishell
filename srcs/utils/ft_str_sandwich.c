#include "minishell.h"

char	*ft_str_sandwich(char *filling, char *bread)
{
	char *sandwich;
	char *bread_with_topping;

	if (!filling)
		return (NULL);
	if (!bread)
		return (ft_strdup(filling));
	bread_with_topping = ft_strjoin(bread, filling);
	if (!bread_with_topping)
		return (NULL);
	sandwich = ft_strjoin(bread_with_topping, bread);
	free(bread_with_topping);
	return (sandwich);
}
