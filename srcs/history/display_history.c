#include "minishell.h"

#define UPKEY		"\033[A"
#define DOWNKEY		"\033[B"

/*
** 現在のlineをhistoryのmodified_lineへ、キー入力の方向へhistoryを参照して表示、lineへコピー
** **histは参照したhisotryをそのまま返す。
*/

static char	*error_dhistory(char *c, char *str)
{
	write(STDOUT_FILENO, "\n", 1);
	ft_putstr_fd("minishell: display_history: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	c[0] = '\n';
	return (NULL);
}

t_dir	get_dir(char *c)
{
	if (!ft_strncmp(c, UPKEY, 4))
		return (NEXT);
	else if (!ft_strncmp(c, DOWNKEY, 4))
		return (PREV);
	return (-1);
}

static void	put_line(char *line, int *i)
{
	extern t_termcap	g_term;

	g_term.cm = wrap_tgetstr(g_term.cm, "cm");
	tputs(tgoto(g_term.cm, g_term.pos[1], g_term.pos[0]), 1, ft_putchar);
	g_term.cd = wrap_tgetstr(g_term.cd, "cd");
	tputs(g_term.cd, 1, ft_putchar);
	*i = (int)ft_strlen(line);
	write(STDOUT_FILENO, line, *i);
	return ;
}

char	*display_history(char *line, char *c, int *i, t_hist **hist)
{
	t_dir	dir;

	dir = get_dir(c);
	if ((dir == NEXT && (*hist)->next == NULL)
		|| (dir == PREV && (*hist)->prev == NULL))
	{
		write(STDOUT_FILENO, "\007", 1);
		return (line);
	}
	if ((*hist)->modified_line != NULL)
		free((*hist)->modified_line);
	(*hist)->modified_line = ft_strdup(line);
	if ((*hist)->modified_line == NULL)
		return (error_dhistory(c, "malloc error"));
	if (dir == NEXT)
		*hist = (*hist)->next;
	else
		*hist = (*hist)->prev;
	if ((*hist)->modified_line == NULL)
		ft_strlcpy(line, (*hist)->line, BUFFER_SIZE);
	else
		ft_strlcpy(line, (*hist)->modified_line, BUFFER_SIZE);
	put_line(line, i);
	return (line);
}
