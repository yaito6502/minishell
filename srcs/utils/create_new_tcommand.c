#include "minishell.h"

t_command *create_new_tcommand(void)
{
	t_command *ptr;

	if (!(ptr = malloc(sizeof(t_command))))
		return (NULL);
	ptr->next = NULL;
	ptr->argv = NULL;
	ptr->redirect_in = NULL;
	ptr->redirect_out = NULL;
	ptr->receive_pipe = false;
	ptr->lastfd[0] = -1;
	ptr->lastfd[1] = -1;
	ptr->pid = -1;
	ptr->op = EOS;
	return (ptr);
}

// int	main(void)
// {
	// t_command *ptr;

	// ptr = create_new_tcommand();
	// printf("%p\n",ptr->next);
	// printf("%p\n",ptr->argv);
	// printf("%p\n",ptr->redirect_in);
	// printf("%p\n",ptr->redirect_out);
	// printf("%d\n",ptr->receive_pipe);
	// printf("%d\n",ptr->lastfd[0]);
	// printf("%d\n",ptr->lastfd[1]);
	// printf("%d\n",ptr->pid);
	// printf("%d\n",ptr->op);
	// return (0);
// }