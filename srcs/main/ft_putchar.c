#include "minishell.h"

int	ft_putchar(int n)
{
	char c;

	c = (char)n;
	write(STDOUT_FILENO, &c, 1);
	return 0;
}