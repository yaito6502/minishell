#include "minishell.h"

/*
** read_line用に端末のカノニカルモードを変更する。
** termcapで使用するospeedを設定。
*/

bool	set_terminal_setting(void)
{
	extern short	ospeed;
	struct termios	termios_p;
	int				ret;

	ret = tcgetattr(STDIN_FILENO, &termios_p);
	if (ret == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (false);
	}
	termios_p.c_lflag &= ~(ICANON | ECHO);
	ospeed = (short)termios_p.c_ospeed;
	ret = tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
	if (ret == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (false);
	}
	return (true);
}

/*
** 変更した端末設定を元に戻す。
*/

bool	reset_terminal_setting(void)
{
	struct termios	termios_p;
	int				ret;

	ret = tcgetattr(STDIN_FILENO, &termios_p);
	if (ret == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (false);
	}
	termios_p.c_lflag &= ICANON | ECHO;
	ret = tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
	if (ret == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (false);
	}
	return (true);
}