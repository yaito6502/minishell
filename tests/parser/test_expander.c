#include "minishell.h"

int main(void)
{
	t_command	*cmd;
	bool		ret;
	// export TEST="$TERM + $PWD"

	cmd = create_new_tcommand();
	cmd->argv = ft_split("'$HOME' aaaa\"$TEST\" $PWD,'test' \"string\" $USER",',');
	ret = preprocess_command(cmd);
	if (ret == true)
		puts("success");
	else
		puts("failure");
	print_tcommand(*cmd);
	free_commandslist(&cmd);
	return 0;
}