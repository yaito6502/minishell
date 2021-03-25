#include "minishell.h"

/*
** 受け取ったlineをdupしてt_historyに格納し、リストの先頭を返す。
** historyは新しい入力順に格納される。直前の入力が先頭に来る。
*/

static t_history	*create_newhistory(void)
{
	t_history *history;

	history = malloc(sizeof(t_history));
	history->next = NULL;
	history->prev = NULL;
	history->line = NULL;
	return (history);
}

t_history			*add_history(t_history *last_history, char *line)
{
	t_history	*new_elm;
	char		*copy;

	if (line == NULL)
		return (NULL);
	copy = ft_strdup(line);
	if (copy == NULL)
		return (NULL);
	new_elm = create_newhistory();
	if (new_elm == NULL)
		return (NULL);
	new_elm->line = copy;
	if (last_history != NULL)
	{
		new_elm->next = last_history;
		last_history->prev = new_elm;
	}
	return (new_elm);
}

bool				free_history(t_history *history)
{
	t_history *tmp;

	if (history == NULL)
		return (false);
	while (history != NULL)
	{
		free(history->line);
		tmp = history;
		history = history->next;
		free(tmp);
	}
	return (true);
}