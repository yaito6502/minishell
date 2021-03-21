#include "minishell.h"

int main(void)
{
	char *line;
	char **tokens;
	int i;

	line = ft_strdup("echo \"a a a a\" hello\"world\"test 'test' $A>outfile");
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