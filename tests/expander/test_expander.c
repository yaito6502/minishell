#include "minishell.h"

static void	print_splits(char *str[])
{
	int i;

	i = 0;
	if (str == NULL)
	{
		printf("\n");
		return ;
	}
	while (str[i] != NULL)
	{
		if (str[i + 1] == NULL)
			printf("%s",str[i]);
		else
			printf("%s, ",str[i]);
		i++;
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	t_command	*cmd;
	bool		ret;

	store_exitstatus(SAVE, 15);
	cmd = create_new_tcommand();
	cmd->argv = ft_split("'$?',$?,\"$?\",\"world's end\",'$HOME'aaaa\"$TEST\",$PWD",',');
	ret = preprocess_command(cmd->argv);
	print_splits(cmd->argv);
	ft_free_split(cmd->argv);

	cmd->argv = ft_split("\"'$?$?'\",'$?',$??,\"world's end\",'$HOME'aaaa\"$TEST\",$PWD",',');
	ret = preprocess_command(cmd->argv);
	print_splits(cmd->argv);
	ft_free_split(cmd->argv);

	cmd->argv = ft_split("\"$?\"$?\"$?\",'$?'$?'$?','','\"\"'",',');
	ret = preprocess_command(cmd->argv);
	print_splits(cmd->argv);
	ft_free_split(cmd->argv);

	cmd->argv = ft_split("\"\'$?\"\'\"$?\', $??, $$$$$$$",',');
	ret = preprocess_command(cmd->argv);
	print_splits(cmd->argv);
	ft_free_split(cmd->argv);

	cmd->argv = ft_split("$$$$$$",',');
	ret = preprocess_command(cmd->argv);
	print_splits(cmd->argv);
	ft_free_split(cmd->argv);

	cmd->argv = ft_split("$$$$$$$",',');
	ret = preprocess_command(cmd->argv);
	print_splits(cmd->argv);

	free_commandslist(&cmd);

	return 0;
}
