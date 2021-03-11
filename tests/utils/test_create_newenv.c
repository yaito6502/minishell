#include "minishell.h"

static void printenv()
{
	extern char **environ;
	int i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	i -= 5;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return ;
}

int main(void)
{
	extern char	**environ;
	int			i;
	bool		ret;

	//free(environ);
	//stack領域のenvironはfreeできない。
	ret = create_newenv();
	printenv();
	ft_free_split(environ);
	//free(environ);
	//新しいenvironはheap領域にあるためfreeできる。
	return (0);
}
