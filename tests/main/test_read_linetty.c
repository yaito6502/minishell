#include "minishell.h"

int main(void)
{
	char *line;

	line = read_linetty();
	puts(line);
	free(line);
	return 0;
}