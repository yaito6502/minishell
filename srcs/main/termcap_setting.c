#include "minishell.h"

bool	init_tterm(void)
{
	extern t_termcap	term;

	term.term_buf = malloc(2048);
	term.string_buf = malloc(2048);
	if (!term.term_buf || !term.string_buf)
	{
		free(term.term_buf);
		free(term.string_buf);
		return (false);
	}
	term.buf_ptr = term.string_buf;
	term.ce = NULL;
	term.dc = NULL;
	term.DC = NULL;
	term.le = NULL;
	return (true);
}

bool	get_terminal_description(void)
{
	extern t_termcap	term;
	char				*termtype;

	termtype = getenv("TERM");
	if (!termtype || tgetent(term.term_buf, termtype) <= 0)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (false);
	}
	return (true);
}

/*
** termios、terminal descriptionからtermcapに必要な情報を取得、外部変数へ設定。
*/

bool	set_termcapsettings(t_termcap term)
{
	struct termios	termios_p;
	extern short	ospeed;
	extern char		PC;
	extern char		*BC;
	extern char		*UP;

	if (tcgetattr(STDOUT_FILENO, &termios_p) == -1)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (false);
	}
	ospeed = (short)termios_p.c_ospeed;
	PC = tgetnum("pc");
	if (PC == -1)
		PC = 0;
	BC = tgetstr("le", &term.buf_ptr);
	UP = tgetstr("up", &term.buf_ptr);
	return (true);
}

/*
** stringbufの枯渇を避けるため、capabilityの再取得を防ぐ
** 利用するcapabilityはtterm内にポインタを保存する
*/

char	*wrap_tgetstr(char *stored_cap, char *cap, char **bufaddr)
{
	if (stored_cap == NULL)
	{
		stored_cap = tgetstr(cap, bufaddr);
		return (stored_cap);
	}
	return (stored_cap);
}

void	free_tterm(t_termcap term)
{
	free(term.term_buf);
	free(term.string_buf);
	return ;
}
