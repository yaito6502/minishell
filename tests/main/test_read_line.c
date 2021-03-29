#include "minishell.h"

int main(void)
{
	char *line;

	line = read_line();
	puts(line);
	free(line);
	return 0;
}