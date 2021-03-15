#include "minishell.h"

/*
** guacamoleのfd上限は256。>,<の前にintに収まる範囲の0~9の数字の連続がある想定。
** fd自体はopenで確認するので、当関数ではエラーチェックしない。
*/

static long	check_fd(char *arg)
{
	long	fd;

	fd = 0;
	if (*arg == '>')
		return (STDOUT_FILENO);
	if (*arg == '<')
		return (STDIN_FILENO);
	while (*arg != '>' && *arg != '<')
	{
		fd = fd * 10 + *arg - '0';
		arg++;
	}
	return (fd);
}

/*
** error出力関数については、要検討。絶対一行にします。
** 案、fork後子プロセスでもpid格納、エラー時pidから子か親か判断して終了動作を変える。
** 親、コマンドリストをクリア、fdをデフォルトに戻して、入力待ちへ。子、終了ステータスを設定してexit()、親でキャッチ。
** エラーメッセージはエラー出力へ
** dup時のBad file descriptorはopenは成功するので空ファイルが生成される。その後の処理は中断。
** open失敗はその場で中断、空ファイルも出来ない。
*/

void		redirect_input(t_command *cmds)
{
	int		i;
	long	ret;
	int		fd;
	int		state;
	int		flag;

	i = 0;
	while (cmds->redirect_in[i] != NULL)
	{
		ret = check_fd(cmds->redirect_in[i]);
		fd = open(cmds->redirect_in[i + 1], O_RDONLY);
		if (fd == -1)
			printf("bash: %s: %s\n", cmds->redirect_in[i + 1], strerror(errno));
		state = dup2(fd, ret);
		if (state == -1)
			printf("bash: %ld: %s\n", ret, strerror(errno));
		close(fd);
		i += 2;
	}
	return ;
}

static bool	is_appending(char *arg)
{
	int i;

	i = ft_strlen(arg);
	if (arg[i - 1] == '>' && arg[i - 2] == '>')
		return (true);
	return (false);
}

void		redirect_output(t_command *cmds)
{
	int		i;
	long	ret;
	int		fd;
	int		state;
	int		flag;

	i = 0;
	while (cmds->redirect_out[i] != NULL)
	{
		ret = check_fd(cmds->redirect_out[i]);
		if (is_appending(cmds->redirect_out[i]))
			flag = O_RDWR | O_CREAT | O_APPEND;
		else
			flag = O_WRONLY | O_CREAT;
		fd = open(cmds->redirect_out[i + 1], flag, S_IRWXU);
		if (fd == -1)
			printf("bash: %s: %s\n", cmds->redirect_out[i + 1], strerror(errno));
		state = dup2(fd, ret);
		if (state == -1)
			printf("bash: %ld: %s\n", ret, strerror(errno));
		close(fd);
		i += 2;
	}
	return ;
}
