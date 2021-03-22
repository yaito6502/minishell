#include "minishell.h"

int main(void)
{
	char *line;
	char **tokens;
	int i;

	line = ft_strdup("echo \"a a a a\" \"world\"hello 'test' 12.34>outfile 500>>outfile2");
	//line = ft_strdup("$A \"world, $USER\" 3>outfile1| ls $HOME;");
	tokens = tokenize(line);
	i = 0;
	while (tokens[i])
	{
		printf("{%s} ", tokens[i]);
		i++;
	}
	return 0;
}