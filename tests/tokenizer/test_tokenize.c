#include "minishell.h"

int main(void)
{
	char *line;
	char **tokens;
	int i;

	line = ft_strdup("echo\ttest \"\thello\t\" 't\ve\rs\ft\n'");
	//line = ft_strdup("\"abc' d\" \"w'o'r'l'd's\" \' a \' b \''\' c \' hello'test string'test 12.34>outfile 500<< >>>outfile2\"'");
	//line = ft_strdup("$A \"world, $USER\" 3>outfile1| ls $HOME;");
	tokens = tokenize(line);
	i = 0;
	while (tokens != NULL && tokens[i])
	{
		printf("{%s} ", tokens[i]);
		i++;
	}
	free(line);
	ft_free_split(tokens);
	return 0;
}
