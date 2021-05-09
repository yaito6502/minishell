#include "minishell.h"

int main(void)
{
	char *line;
	extern t_termcap g_term;

	init_tterm();
	get_terminal_description();
	set_termcapsettings(g_term);

	line = read_line();
	puts(line);
	free(line);
	return 0;
}