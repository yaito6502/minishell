#include "minishell.h"

#define UPKEY		"\033[A"
#define DOWNKEY		"\033[B"
#define RIGHTKEY	"\033[C"
#define LEFTKEY		"\033[D"
#define BACKSPACE	"\177"
#define TAB			"\t"
#define CTRL_D		"\004"
#define CTRL_C		"\003"

void	move_nextline(int *len)
{
	int	col;

	get_terminal_description();
	col = tgetnum("col");
	if ((13 + *len) % col == 0)
	{
		ft_putchar(13);
		ft_putchar(10);
	}
}

static char	*check_input(char *line, char *c, int *i)
{
	int	n;

	n = 0;
	while (c[n] != '\0' && c[n] != '\n' && c[n] != '\033')
	{
		if (*i == BUFFER_SIZE)
			break ;
		ft_putchar_fd(c[n], STDOUT_FILENO);
		move_nextline(i);
		line[*i] = c[n];
		(*i)++;
		n++;
	}
	line[*i] = '\0';
	return (line);
}

static bool	check_control(char *c, int *i, char *line, t_hist **hist)
{
	if (!ft_strncmp(c, BACKSPACE, 2) || !ft_strncmp(c, TAB, 2)
		|| !ft_strncmp(c, CTRL_D, 2) || !ft_strncmp(c, CTRL_C, 2)
		|| !ft_strncmp(c, UPKEY, 4) || !ft_strncmp(c, DOWNKEY, 4))
	{
		if (!ft_strncmp(c, CTRL_D, 2) && *i == 0)
			get_eof(line, hist);
		else if (!ft_strncmp(c, CTRL_D, 2) || !ft_strncmp(c, TAB, 2))
			write(1, "\007", 1);
		else if (!ft_strncmp(c, BACKSPACE, 2))
			back_line(line, i);
		else if (!ft_strncmp(c, CTRL_C, 2))
			get_sigint(line, c);
		else if (!ft_strncmp(c, UPKEY, 4) || !ft_strncmp(c, DOWNKEY, 4))
			display_history(line, c, i, hist);
		return (true);
	}
	if (*i == BUFFER_SIZE)
	{
		write(1, "\007", 1);
		return (true);
	}
	return (false);
}

static char	*get_line(char *line, t_hist **hist)
{
	char	c[64];
	int		i;
	int		rc;

	i = 0;
	c[0] = '\0';
	while (c[0] != '\n')
	{
		rc = read(STDIN_FILENO, c, 63);
		if (rc == -1)
			return (NULL);
		c[rc] = '\0';
		if (rc != 0 && !check_control(c, &i, line, hist))
			line = check_input(line, c, &i);
	}
	return (line);
}

char	*read_line(t_hist **hist)
{
	extern t_termcap	term;
	char				*line;
	char				*tmp;

	line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line || !set_terminal_setting())
	{
		free(line);
		return (NULL);
	}
	line[0] = '\0';
	tmp = line;
	get_cursor_position(&term.pos[0], &term.pos[1]);
	line = get_line(line, hist);
	if (!reset_terminal_setting() || !line)
	{
		free(tmp);
		return (NULL);
	}
	write(STDOUT_FILENO, "\n", 1);
	if (!update_history(line, hist))
		return (NULL);
	return (line);
}
