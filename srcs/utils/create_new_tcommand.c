#include "minishell.h"

/*
** 新しいt_commandを作成、そのポインター型変数を返す。
*/

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
	ptr->has_childproc = false;
	return (ptr);
}
