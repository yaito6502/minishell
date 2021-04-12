#include "minishell.h"

void	sigint_handler(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n", 1);
	store_exitstatus(SAVE, 130);
}

void	sigquit_handler(int signal)
{
	(void)signal;
	//write(STDOUT_FILENO, "Quit\n", 5);
	store_exitstatus(SAVE, 131);
}
