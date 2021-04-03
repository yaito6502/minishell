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
	extern t_termcap term;
	char *str;

	init_tterm();
	get_terminal_description();
	set_termcapsettings(term);
	str = tgetstr("cl", &term.buf_ptr);
	tputs(str, 1, ft_putchar);
	free_tterm(term);
	return (0);
}