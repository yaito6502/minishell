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
	extern t_termcap	g_term;
	int					col;
	int					i;

	get_terminal_description();
	col = tgetnum("col");
	g_term.up = wrap_tgetstr(g_term.up, "up");
	g_term.nd = wrap_tgetstr(g_term.nd, "nd");
	g_term.dc = wrap_tgetstr(g_term.dc, "dc");
	tputs(g_term.up, 1, ft_putchar);
	i = 0;
	while (i < col)
	{
		tputs(g_term.nd, 1, ft_putchar);
		i++;
	}
	tputs(g_term.dc, 1, ft_putchar);
}

void	back_line(char *line, int *i)
{
	extern t_termcap	g_term;

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
	g_term.le = wrap_tgetstr(g_term.le, "le");
	g_term.dc = wrap_tgetstr(g_term.dc, "dc");
	tputs(g_term.le, 1, ft_putchar);
	tputs(g_term.dc, 1, ft_putchar);
	return ;
}
