#include "minishell.h"

int	ft_putchar(int n)
{
	char c;

	c = (char)n;
	write(1, &c, 1);
	return (1);
}

int	main(void)
{
	extern t_termcap g_term;
	char *str;

	init_tterm();
	get_terminal_description();
	set_termcapsettings(g_term);
	str = tgetstr("cl", &g_term.buf_ptr);
	tputs(str, 1, ft_putchar);
	free_tterm(g_term);
	return (0);
}