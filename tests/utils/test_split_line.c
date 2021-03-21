#include "minishell.h"

#define SPACES " \t\n\v\f\r"

void	print_strs(char **list)
{
	size_t i;

	if (!list)
		return ;
	i = 0;
	while (list[i] != NULL)
	{
		printf("%s,", list[i]);
		i++;
	}
}

void	free_strs(char **list)
{
	size_t i;

	if (!list)
		return ;
	i = 0;
	while (list[i] != NULL)
		free(list[i++]);
	free(list);
}

int		main(void)
{
	char **strs;
	char *set1[2] = {SPACES, ";&|<>"};
	char *set2[2] = {SPACES, ":!"};

	strs = split_line("echo hello>file1>file2 world;cat < file2|head -n 1|wc;", set1);
	print_strs(strs);
	free_strs(strs);
	strs = split_line("hello : 42: Tokyo!:", set2);
	print_strs(strs);
	free_strs(strs);
	return (0);
}
