#include "minishell.h"

#define UPKEY		"\033[A"
#define DOWNKEY		"\033[B"
#define RIGHTKEY	"\033[C"
#define LEFTKEY		"\033[D"

/*
** 端末のカノニカルモードを無効化し、read関数から入力を即時受け取る。
** コマンド実行中の標準入力への影響は未検証、
*/

static void	back_line(char *line, int *i)
{
	line[*i - 1] = '\0';
	*i = *i - 1;
	//termcapを使ってカーソルを左へ移動、カーソル上の文字削除
	return ;
}

static char	*get_line(char *line)
{
	char	c[8];
	int		i;
	int		rc;

	c[0] = '\0';
	i = 0;
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
			back_line(line, &i);
		if (rc == 1 && c[0] != '\n' && c[0] != '\177')
		{
			ft_putchar_fd(c[0], STDOUT_FILENO);
			line[i++] = c[0];
			line[i] = '\0';
		}
	}
	return (line);
}

char		*read_line(void)
{
	char	*line;
	char	*tmp;

	line = malloc(sizeof(char) * 2048);
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
