#include "minishell.h"

#define BUFFER_SIZE	2048

char	*get_eof(char *line, char *c, int i)
{
	if (i != 0)
	{
		write(1, "\007", 1);
		return (line);
	}
	ft_strlcpy(line, "exit", BUFFER_SIZE);
	write(1, line, 4);
	ft_strlcpy(c, "\n", 8);
	return (line);
}


//lineクリア、\n送信
char	*get_sigint(char *line, char *c)
{
	line[0] = '\0';
	ft_strlcpy(c, "\n", 8);
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