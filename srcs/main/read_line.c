#include "minishell.h"

#define BUFFER_SIZE	2048

#define UPKEY		"\033[A"
#define DOWNKEY		"\033[B"
#define RIGHTKEY	"\033[C"
#define LEFTKEY		"\033[D"
#define BACKSPACE	"\177"
#define CTRL_D		"\004"

/*
** 端末のカノニカルモードを無効化し、read関数から入力を即時受け取る。
*/

static void	exit_while_read(char *line)
{
	extern char			**environ;
	extern t_termcap	term;

	ft_free_split(environ);
	free(line);
	//free hist
	reset_terminal_setting();
	free_tterm(term);
	write(STDOUT_FILENO, "exit\n", 5);
	exit(EXIT_SUCCESS);
}

static void	back_line(char *line, int *i)
{
	extern t_termcap term;

	if (*i == 0)
	{
		write(1, "\007", 1);
		return ;
	}
	line[*i - 1] = '\0';
	*i = *i - 1;
	term.le = wrap_tgetstr(term.le, "le", &term.buf_ptr);
	term.dc = wrap_tgetstr(term.dc, "dc", &term.buf_ptr);
	tputs(term.le, 1, ft_putchar);
	tputs(term.dc, 1, ft_putchar);
	return ;
}

static char	*check_input(char *line, char *c, int *i, int rc)
{
	if (*i == BUFFER_SIZE)
	{
		ft_putendl_fd("minishell: read_line: Too long line", 2);
		return (NULL);
	}
	//if (!ft_strncmp(c, UPKEY, 4) || !ft_strncmp(c, DOWNKEY, 4))
	//現在のlineをhistoryへ追加、termcapで表示消去、historyから表示。lineにコピー
	if (!ft_strncmp(c, BACKSPACE, 2))
		back_line(line, i);
	else if (rc == 1 && c[0] != '\n')
	{
		ft_putchar_fd(c[0], STDOUT_FILENO);
		line[*i] = c[0];
		(*i)++;
		line[*i] = '\0';
	}
	return (line);
}

static char	*get_line(char *line)
{
	char	c[8];
	int		i;
	int		rc;

	i = 0;
	c[0] = '\0';
	while (c[0] != '\n')
	{
		rc = read(STDIN_FILENO, c, 7);
		if (rc == -1)
			return (NULL);
		c[rc] = '\0';
		if (rc != 0 && c[0] == '\004' && c[1] == '\0')
			if (i == 0)
				exit_while_read(line);
			else
				write(1, "\007", 1);
		else if (rc != 0)
			line = check_input(line, c, &i, rc);
	}
	return (line);
}

char		*read_line(void)
{
	char	*line;
	char	*tmp;

	line = malloc(sizeof(char) * BUFFER_SIZE);
	if (!line || !set_terminal_setting())
	{
		free(line);
		return (NULL);
	}
	tmp = line;
	line = get_line(line);
	if (!line || !reset_terminal_setting())
	{
		free(tmp);
		return (NULL);
	}
	write(1, "\n", 1);
	return (line);
}
