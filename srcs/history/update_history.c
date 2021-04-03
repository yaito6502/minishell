#include "minishell.h"

/*
** コマンドが実行される前に、実行されるlineは新しいhistoryのlineへ
** 実行されなかったhistoryのmodified_lineはlineへ更新する。
*/

static bool		error_return(char *str)
{
	write(1, "\n", 1);
	ft_putstr_fd("minishell: update_history: ", 2);
	ft_putendl_fd(str, 2);
	return (false);
}

static t_hist	*delete_added_elm(t_hist *hist_p)
{
	t_hist *tmp;

	while (hist_p->prev != NULL)
		hist_p = hist_p->prev;
	tmp = hist_p->next;
	free_one_elm(hist_p);
	hist_p = tmp;
	if (hist_p == NULL)
		return (NULL);
	hist_p->prev = NULL;
	return (hist_p);
}

static t_hist	*add_line_to_front(char *line, t_hist *hist_p)
{
	free(hist_p->modified_line);
	hist_p->modified_line = NULL;
	while (hist_p->prev != NULL)
		hist_p = hist_p->prev;
	hist_p->line = ft_strdup(line);
	if (hist_p->line == NULL)
		return (NULL);
	return (hist_p);
}

static void		replace_modified_line(t_hist *hist_p)
{
	while (hist_p != NULL)
	{
		if (hist_p->modified_line != NULL)
		{
			free(hist_p->line);
			hist_p->line = hist_p->modified_line;
			hist_p->modified_line = NULL;
		}
		hist_p = hist_p->next;
	}
	return ;
}

bool			update_history(char *line, t_hist **hist)
{
	t_hist	*hist_p;

	if (*line == '\0')
	{
		*hist = delete_added_elm(*hist);
		if (*hist == NULL)
			return (true);
		hist_p = *hist;
	}
	else
	{
		*hist = add_line_to_front(line, *hist);
		if (*hist == NULL)
			return (error_return("malloc error"));
		free((*hist)->modified_line);
		(*hist)->modified_line = NULL;
		if ((*hist)->next == NULL)
			return (true);
		hist_p = (*hist)->next;
	}
	replace_modified_line(hist_p);
	return (true);
}
