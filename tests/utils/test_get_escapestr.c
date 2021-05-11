#include "minishell.h"

int	main()
{
	char	*line;
	char	*ret;

	//line = ft_strdup("h\\e\\\\l\\lo\"t\\\\es\\t\"'wo\\rl\\d't\\est\\");
	line = ft_strdup("unset ' \\\"$&`\\n'");
	printf("input : %s\n", line);
	ret = get_escapestr(line);
	printf("output: %s\n", ret);
	free(line);
	free(ret);
	return 0;
}