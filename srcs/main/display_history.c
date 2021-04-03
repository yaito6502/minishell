#include "minishell.h"

#define UPKEY		"\033[A"
#define DOWNKEY		"\033[B"

/*
** 現在のlineをhistoryのmodified_lineへ、キー入力の方向へhistoryを参照して表示、lineへコピー
** **histは参照したhisotryをそのまま返す。
** コマンドが実行される前に、実行されるlineは新しいhistoryのlineへ
** 実行されなかったhistoryのmodified_lineはlineへ更新する。
*/

char	*error_return(char *c, char *str)
{
	write(1, "\n", 1);
	ft_putstr_fd("minishell: display_history: ", 2);
	ft_putendl_fd(str, 2);
	c[0] = '\n';
	return (NULL);
}

void	put_line(char *line, int *i)
{
	extern t_termcap term;

	//カーソル位置を文字列頭へ
	term.le = wrap_tgetstr(term.le, "le", &term.buf_ptr);
	while (i > 0)
	{
		tputs(term.le, 1, ft_putchar);
		i--;
	}
	//文字列削除
	term.ce = wrap_tgetstr(term.ce, "ce", &term.buf_ptr);
	tputs(term.ce, 1, ft_putchar);
}

char	*display_history(char *line, char *c, int *i, t_hist **hist)
{
	t_dir dir;

	if (!ft_strncmp(c, UPKEY, 4))
		dir = NEXT;
	else
		dir = PREV;
	if ((dir == NEXT && (*hist)->next == NULL) ||
		(dir == PREV && (*hist)->prev == NULL))
	{
		write(1, "\007", 1);
		return (line);
	}
	(*hist)->modified_line = ft_strdup(line);
	if ((*hist)->modified_line == NULL)
		return (error_return(c, "malloc error"));
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

/*
	//カーソル位置を文字列頭へ
	term.le = wrap_tgetstr(term.le, "le", &term.buf_ptr);
	while (i > 0)
	{
		tputs(term.le, 1, ft_putchar);
		i--;
	}
	//文字列削除
	term.ce = wrap_tgetstr(term.ce, "ce", &term.buf_ptr);
	tputs(term.ce, 1, ft_putchar);
*/