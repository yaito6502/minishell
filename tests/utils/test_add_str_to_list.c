#include "minishell.h"

void	print_list(char **list)
{
	size_t i;

	i = 0;
	if (!list)
	{
		printf("NULL\n\n");
		return ;
	}
	while (list[i] != NULL)
	{
		printf("%zu : %s\n", i, list[i]);
		i++;
	}
	printf("\n");
}

int		main(void)
{
	char	**list;
	size_t	i;

	list = NULL;
	list = add_str_to_list(list, NULL);
	print_list(list);
	list = add_str_to_list(list, "Hello");
	print_list(list);
	list = add_str_to_list(list, "this is");
	print_list(list);
	list = add_str_to_list(list, "");
	print_list(list);
	list = add_str_to_list(list, "test");
	print_list(list);
	list = add_str_to_list(list, NULL);
	print_list(list);
	system("leaks test");
	return (0);
}
