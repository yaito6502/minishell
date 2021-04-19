#include "minishell.h"

bool	is_leftend(int *i)
{
	int	col;

	get_terminal_description();
	col = tgetnum("col");
	if ((13 + *i) % col == 0)
		return (true);
	return (false);
}

static void	move_rightend(void)
{
	extern t_termcap	term;
	int					col;
	int					i;

	get_terminal_description();
	col = tgetnum("col");
	term.up = wrap_tgetstr(term.up, "up");
	term.nd = wrap_tgetstr(term.nd, "nd");
	term.dc = wrap_tgetstr(term.dc, "dc");
	tputs(term.up, 1, ft_putchar);
	i = 0;
	while (i < col)
	{
		tputs(term.nd, 1, ft_putchar);
		i++;
	}
	tputs(term.dc, 1, ft_putchar);
}

void	back_line(char *line, int *i)
{
	extern t_termcap	term;

	if (*i == 0)
	{
		write(STDOUT_FILENO, "\007", 1);
		return ;
	}
	line[*i - 1] = '\0';
	*i = *i - 1;
	if (is_leftend(i))
	{
		move_rightend();
		return ;
	}
	term.le = wrap_tgetstr(term.le, "le");
	term.dc = wrap_tgetstr(term.dc, "dc");
	tputs(term.le, 1, ft_putchar);
	tputs(term.dc, 1, ft_putchar);
	return ;
}
