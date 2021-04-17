#include "minishell.h"

void	get_cursor_position(int *row, int *col)
{
	int		i;
	char	buf[255];
	int		rc;

	write(0, "\033[6n", 4);
	rc = read(0, buf, 254);
	buf[rc] = '\0';
	i = 1;
	while (buf[i] != '\0' && !ft_isdigit(buf[i]))
		i++;
	*row = ft_atoi(&buf[i]) - 1;
	while (buf[i] != '\0' && ft_isdigit(buf[i]))
		i++;
	i++;
	*col = ft_atoi(&buf[i]) - 1;
}

void	get_initial_position(int *len, int *row, int *col)
{
	int					tcol;
	extern t_termcap	term;

	get_cursor_position(row, col);
	get_terminal_description();
	tcol = tgetnum("col");
	*row = *row - ((13 + *len) / tcol);
	*col = *col - ((13 + *len) % tcol);
	term.cm = wrap_tgetstr(term.cm, "cm");
	tputs(tgoto(term.cm, *col + 13, *row), 1, ft_putchar);
}
