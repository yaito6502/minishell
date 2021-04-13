#include "minishell.h"

#define UPKEY		"\033[A"
#define DOWNKEY		"\033[B"
#define RIGHTKEY	"\033[C"
#define LEFTKEY		"\033[D"
#define BACKSPACE	"\177"
#define CTRL_D		"\004"
#define CTRL_C		"\003"

/*
** 端末のカノニカルモードを無効化し、read関数から入力を即時受け取る。
*/

static void	back_line(char *line, int *i)
{
	extern t_termcap	term;

	if (*i == 0)
	{
		write(STDOUT_FILENO, "\007", 1);
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
		write(STDOUT_FILENO, "\n", 1);
		ft_putendl_fd("minishell: read_line: Too long line", STDERR_FILENO);
		c[0] = '\n';
		return (NULL);
	}
	if (!ft_strncmp(c, BACKSPACE, 2))
		back_line(line, i);
	else if (!ft_strncmp(c, "\v", 2) || !ft_strncmp(c, "\r", 2)
		|| !ft_strncmp(c, "\f", 2) || !ft_strncmp(c, "\t", 2))
		write(STDOUT_FILENO, "\007", 1);
	else if (rc == 1 && c[0] != '\n' && c[0] != '\034')
	{
		ft_putchar_fd(c[0], STDOUT_FILENO);
		line[*i] = c[0];
		(*i)++;
		line[*i] = '\0';
	}
	return (line);
}

static char	*get_line(char *line, t_hist **hist)
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
		if (rc != 0 && !ft_strncmp(c, CTRL_D, 2) && i == 0)
			get_eof(line, hist);
		else if (rc != 0 && !ft_strncmp(c, CTRL_D, 2))
			write(1, "\007", 1);
		else if (rc != 0 && !ft_strncmp(c, CTRL_C, 2))
			line = get_sigint(line, c);
		else if (!ft_strncmp(c, UPKEY, 4) || !ft_strncmp(c, DOWNKEY, 4))
			line = display_history(line, c, &i, hist);
		else if (rc != 0)
			line = check_input(line, c, &i, rc);
	}
	return (line);
}

char	*read_line(t_hist **hist)
{
	char	*line;
	char	*tmp;

	line = malloc(sizeof(char) * BUFFER_SIZE);
	if (!line || !set_terminal_setting())
	{
		free(line);
		return (NULL);
	}
	line[0] = '\0';
	tmp = line;
	line = get_line(line, hist);
	write(STDOUT_FILENO, "\n", 1);
	if (!reset_terminal_setting() || !line)
	{
		free(tmp);
		return (NULL);
	}
	if (!update_history(line, hist))
		return (NULL);
	return (line);
}
