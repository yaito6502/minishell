#include "minishell.h"

bool	init_tterm(void)
{
	extern t_termcap	g_term;

	g_term.term_buf = malloc(2048);
	g_term.string_buf = malloc(2048);
	if (!g_term.term_buf || !g_term.string_buf)
	{
		free(g_term.term_buf);
		free(g_term.string_buf);
		return (false);
	}
	g_term.buf_ptr = g_term.string_buf;
	g_term.cd = NULL;
	g_term.dc = NULL;
	g_term.up = NULL;
	g_term.nd = NULL;
	g_term.le = NULL;
	g_term.cm = NULL;
	return (true);
}

bool	get_terminal_description(void)
{
	extern t_termcap	g_term;
	char				*termtype;

	termtype = getenv("TERM");
	if (!termtype || tgetent(g_term.term_buf, termtype) <= 0)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (false);
	}
	return (true);
}

/*
** termios、terminal descriptionからtermcapに必要な情報を取得、外部変数へ設定。
*/

bool	set_termcapsettings(t_termcap g_term)
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
	BC = tgetstr("le", &g_term.buf_ptr);
	UP = tgetstr("up", &g_term.buf_ptr);
	return (true);
}

/*
** stringbufの枯渇を避けるため、capabilityの再取得を防ぐ
** 利用するcapabilityはtterm内にポインタを保存する
*/

char	*wrap_tgetstr(char *stored_cap, char *cap)
{
	extern t_termcap	g_term;

	if (stored_cap == NULL)
	{
		stored_cap = tgetstr(cap, &g_term.buf_ptr);
		return (stored_cap);
	}
	return (stored_cap);
}

void	free_tterm(t_termcap g_term)
{
	free(g_term.term_buf);
	free(g_term.string_buf);
	return ;
}
