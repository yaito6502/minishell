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

	cmd->argv = ft_split("echo,\"$\t$\v$USER $ \"'$PWD'",',');
	ret = preprocess_command(cmd);
	print_splits(cmd->argv);
	ft_free_split(cmd->argv);

	cmd->argv = ft_split("~test,~,\"~\",'~',\" ~\",~/test,test/~,~/~/,test~",',');
	ret = preprocess_command(cmd);
	print_splits(cmd->argv);
	ft_free_split(cmd->argv);

	cmd->argv = ft_split("echo,a,$TEST,a,$123456789USER",',');
	ret = preprocess_command(cmd);
	print_splits(cmd->argv);
	ft_free_split(cmd->argv);

	cmd->argv = ft_split("echo,$USER'$USER'text,oui,$USER,''", ',');
	ret = preprocess_command(cmd);
	print_splits(cmd->argv);
	ft_free_split(cmd->argv);

	cmd->argv = ft_split("'$?',$?,\"$?\",\"world's end\",'$HOME'aaaa\"$TEST\",$PWD",',');
	ret = preprocess_command(cmd);
	print_splits(cmd->argv);
	ft_free_split(cmd->argv);

	cmd->argv = ft_split("\"'$?$?'\",'$?',$??,\"world's end\",'$HOME'aaaa\"$TEST\",$PWD",',');
	ret = preprocess_command(cmd);
	print_splits(cmd->argv);
	ft_free_split(cmd->argv);

	cmd->argv = ft_split("\"$?\"$?\"$?\",'$?'$?'$?','','\"\"'",',');
	ret = preprocess_command(cmd);
	print_splits(cmd->argv);
	ft_free_split(cmd->argv);

	cmd->argv = ft_split("\"\'$?\"\'\"$?\', $??, $$$$$$$",',');
	ret = preprocess_command(cmd);
	print_splits(cmd->argv);
	ft_free_split(cmd->argv);

	cmd->argv = ft_split("$$$$$$",',');
	ret = preprocess_command(cmd);
	print_splits(cmd->argv);
	ft_free_split(cmd->argv);

	cmd->argv = ft_split("$$$$$$$",',');
	ret = preprocess_command(cmd);
	print_splits(cmd->argv);

	free_commandslist(&cmd);

	return 0;
}
