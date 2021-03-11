#include "minishell.h"

int main(void)
{
	extern char	**environ;
	int			i;
	bool		ret;

	//free(environ);
	//stack領域のenvironはfreeできない。
	ret = create_newenv();
	i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	free(environ);
	//新しいenvironはheap領域にあるためfreeできる。
	return (0);
}
