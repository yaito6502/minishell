#include "minishell.h"

/*
** 各コマンド終了後、終了ステータスを格納する関数。
** 終了ステータスを入力(0, exit status)、出力(1, 0)
** 終了ステータスは0~255、
*/

int	store_exitstatus(int mode, int last_status)
{
	static int	exit_status = 0;

	if (mode != 0 && mode != 1)
		return (-1);
	if (mode == 0)
	{
		exit_status = last_status;
	}
	return (exit_status);
}