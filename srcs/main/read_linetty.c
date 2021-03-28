#include "minishell.h"

#define UPKEY		"\033[A"
#define DOWNKEY		"\033[B"
#define RIGHTKEY	"\033[C"
#define LEFTKEY		"\033[D"

/*
** 端末のカノニカルモードを無効化し、read関数から入力を即時受け取る。
** コマンド実行中の標準入力への影響は未検証、
*/

static bool	set_terminal_setting(void)
{
	struct termios	termios_p;
	int				ret;

	ret = tcgetattr(STDIN_FILENO, &termios_p);
	if (ret == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (false);
	}
	termios_p.c_lflag &= ~(ICANON | ECHO);
	ret = tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
	if (ret == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (false);
	}
	return (true);
}

static char	*back_line(char *line, int *i)
{
	line[*i - 1] = '\0';
	*i = *i - 1;
	//termcapを使ってカーソルを左へ移動、カーソル上の文字削除
	return (line);
}

static char	*get_line(char *line, int i, int rc)
{
	char	c[8];

	c[0] = '\0';
	while (c[0] != '\n')
	{
		rc = read(STDIN_FILENO, c, 7);
		if (rc == -1)
		{
			free(line);
			return (NULL);
		}
		c[rc] = '\0';
		if (!ft_strncmp(c, UPKEY, 4) || !ft_strncmp(c, DOWNKEY, 4))
			//termcapで現在のを消去、historyから表示。lineにコピー
		if (rc != 0 && !ft_strncmp(c, "\177", 2))
			line = back_line(line, &i);
		if (rc == 1 && c[0] != '\n' && c[0] != '\177')
		{
			ft_putchar_fd(c[0], STDOUT_FILENO);
			line[i++] = c[0];
			line[i] = '\0';
		}
	}
	return (line);
}

char		*read_linetty(void)
{
	char			*line;
	int				i;
	int				rc;

	line = malloc(sizeof(char) * 2048);
	if (!line)
		return (NULL);
	if (!set_terminal_setting())
	{
		free(line);
		return (NULL);
	}
	i = 0;
	line = get_line(line, i, rc);
	if (line == NULL)
		return (NULL);
	write(1, "\n", 1);
	return (line);
}
