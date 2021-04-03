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

static int	is_appending(char *arg)
{
	int i;

	i = ft_strlen(arg);
	if (arg[i - 1] == '>' && arg[i - 2] == '>')
		return (O_RDWR | O_CREAT | O_APPEND);
	return (O_WRONLY | O_CREAT);
}

/*
** dup時のBad file descriptorはopenは成功するので空ファイルが生成される。その後の処理は中断。
** open失敗はその場で中断、空ファイルも出来ない。
*/

bool		redirect_input(t_command *cmd)
{
	int		i;
	long	target_fd;
	int		fd;
	int		ret;

	i = 0;
	while (cmd->redirect_in && cmd->redirect_in[i] != NULL)
	{
		target_fd = check_fd(cmd->redirect_in[i]);
		fd = open(cmd->redirect_in[i + 1], O_RDONLY);
		if (fd == -1)
			return (redirect_error(cmd->redirect_in[i + 1], NULL));
		ret = dup2(fd, target_fd);
		close(fd);
		if (ret == -1)
			return (fd_error(target_fd, NULL));
		i += 2;
	}
	return (true);
}

bool		redirect_output(t_command *cmd)
{
	int		i;
	long	target_fd;
	int		fd;
	int		ret;

	i = 0;
	while (cmd->redirect_out && cmd->redirect_out[i] != NULL)
	{
		target_fd = check_fd(cmd->redirect_out[i]);
		ret = is_appending(cmd->redirect_out[i]);
		fd = open(cmd->redirect_out[i + 1], ret, S_IRWXU);
		if (fd == -1)
			return (redirect_error(cmd->redirect_out[i + 1], NULL));
		ret = dup2(fd, target_fd);
		close(fd);
		if (ret == -1)
			return (fd_error(target_fd, NULL));
		i += 2;
	}
	return (true);
}

bool		do_redirection(t_command *cmd)
{
	bool	ret;

	ret = redirect_input(cmd);
	if (ret == false)
		return (false);
	ret = redirect_output(cmd);
	if (ret == false)
		return (false);
	return (true);
}