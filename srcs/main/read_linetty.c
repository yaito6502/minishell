#include "minishell.h"

/*
** 端末のカノニカルモードを無効化し、read関数から入力を即時受け取る。
*/

#define UPKEY		"\033[A"
#define DOWNKEY		"\033[B"
#define RIGHTKEY	"\033[C"
#define LEFTKEY		"\033[D"

static bool set_terminal_setting(void)
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
	line[*i] = '\0';
	*i = *i - 1;
	//termcapを使ってカーソルを左へ移動、カーソル上の文字削除
	return (line);
}

char	*read_linetty(void)
{
	char			c;
	char			*line;
	int				i;
	int				rc;

	if (!set_terminal_setting())
		return (NULL);
	line = malloc(sizeof(char) * 2048);
	i = 0;
	while (c != '\n')
	{
		rc = read(STDIN_FILENO, &c, 1);
		if (rc != 0 && c == '\177')
		{
			line = back_line(line, &i);
			continue ;
		}
		if (rc != 0 && c != '\n')
		{
			ft_putchar_fd(c, STDOUT_FILENO);
			line[i] = c;
			line[i + 1] = '\0';
			i++;
		}
	}
	puts("");
	return (line);
}