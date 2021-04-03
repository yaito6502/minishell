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

t_hist			*add_history(t_hist *last_hist, char *line)
{
	t_hist		*new_elm;
	char		*copy;

	copy = ft_strdup(line);
	if (copy == NULL)
		return (NULL);
	new_elm = create_newhistory();
	if (new_elm == NULL)
		return (NULL);
	new_elm->line = copy;
	if (last_hist != NULL)
	{
		new_elm->next = last_hist;
		last_hist->prev = new_elm;
	}
	return (new_elm);
}

void				free_history(t_hist *hist)
{
	t_hist *tmp;

	while (hist != NULL)
	{
		free(hist->line);
		tmp = hist;
		hist = hist->next;
		free(tmp);
	}
}
