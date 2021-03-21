#include "minishell.h"

int main(void)
{
	char *line;
	char **tokens;
	int i;

	line = ft_strdup("echo \"a a a a\" hello\"world\"test 'test' $A>outfile");
	tokens = tokenize(line);
	i = 0;
	while (tokens[i])
	{
		printf("{%s} ", tokens[i]);
		i++;
	}
	return 0;
}