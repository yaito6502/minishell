#include "minishell.h"

/*
** 受け取ったlineをdupしてt_historyに格納し、リストの先頭を返す。
** historyは新しい入力順に格納される。直前の入力が先頭に来る。
*/

static t_hist	*create_newhistory(void)
{
	t_hist *hist;

	hist = malloc(sizeof(t_hist));
	if (hist == NULL)
		return (NULL);
	hist->next = NULL;
	hist->prev = NULL;
	hist->line = NULL;
	hist->modified_line = NULL;
	return (hist);
}

t_hist			*add_newelm_to_hist(t_hist *hist)
{
	t_hist	*new_elm;

	new_elm = create_newhistory();
	if (new_elm == NULL)
		return (NULL);
	if (hist != NULL)
	{
		new_elm->next = hist;
		hist->prev = new_elm;
	}
	return (new_elm);
}

void				free_history(t_hist *hist)
{
	t_hist *tmp;

	while (hist->prev != NULL)
		hist = hist->prev;
	while (hist != NULL)
	{
		tmp = hist->next;
		free_one_elm(hist);
		hist = tmp;
	}
}

void				free_one_elm(t_hist *hist)
{
	if (hist->line != NULL)
		free(hist->line);
	if (hist->modified_line != NULL)
		free(hist->modified_line);
	free(hist);
	return ;
}