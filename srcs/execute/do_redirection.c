#include "minishell.h"

void		redirect_input(t_command *cmds)
{
	int	i;
	int fd;

	i = 0;
	while (cmds->redirect_in[i] != NULL)
	{
		fd = open(cmds->redirect_in[i], O_RDONLY);
		if (fd = -1)
			//error出力関数、パース後エラーチェック挟んだほうがよい？
		dup2(fd, 0);
		close(fd);
		i++;
	}
}

static int	check_fd(char *arg)
{
	if(!ft_strcmp(arg, ">") || !ft_strcmp(arg, "1>"))
		return (1);
	if(!ft_strcmp(arg, "2>"))
		return (2);
	return (0);
}

void		redirect_output(t_command *cmds)
{
	int	i;
	int	ret;
	int	fd;

	i = 0;
	while (cmds->redirect_out[i] != NULL)
	{
		ret = check_fd(cmds->redirect_out[i]);
		fd = open(cmds->redirect_out[i + 1], O_WRONLY | O_CREAT);
		if (fd = -1)
			//error
		dup2(fd, ret);
		close(fd);
		i = i + 2;
	}
}