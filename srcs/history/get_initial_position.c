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
