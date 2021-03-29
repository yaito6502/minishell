#include "minishell.h"

int main(void)
{
	t_command	*cmd;
	bool		ret;
	size_t		i = 0;
	// export TEST="$TERM + $PWD"

	cmd = create_new_tcommand();
	cmd->argv = ft_split("\"\"world's end\",'$HOME' aaaa\"$TEST\" $PWD,'\"tes\"t\"' $USER\"",',');
	/*while (cmd->argv[i] != NULL)
		puts(cmd->argv[i++]);*/
	ret = preprocess_command(cmd);
	if (ret == true)
		puts("success");
	else
		puts("failure");
	print_tcommand(*cmd);
	free_commandslist(&cmd);
	return 0;
}
