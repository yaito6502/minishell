#include "minishell.h"

t_command	*create_new_tcommand(void)
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


//
//int	main(void)
//{
//	t_command *ptr;
//
//	ptr = create_new_tcommand();
//	print_tcommand(*ptr);
//	return (0);
//}