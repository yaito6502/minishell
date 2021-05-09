#include "../includes/minishell.h"

void	sigint_handler(int signal)
{
	printf("\nrecieved sigint [%d]\n", signal);
}

void	sigquit_handler(int signal)
{
	printf("\nrecieved sigquit [%d]\n", signal);
}
/*
int		main(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR || signal(SIGQUIT, sigquit_handler) == SIG_ERR)
	{
		printf("\nsignal error\n");
		return (EXIT_FAILURE);
	}
	sleep(100);
	return (EXIT_SUCCESS);
}*/
