#include "minishell.h"

int main(void)
{
	t_command *cmd;
	int rc;
	char buf[25];
	int fd;

	cmd = create_new_tcommand();
	cmd->redirect_in = ft_split("<,./testinout/infile1,50<,./testinout/infile2",',');
	cmd->redirect_out = ft_split(">,testinout/outfile1,99999999>>,testinout/outfile500",',');
	print_tcommand(*cmd);
	do_redirection(cmd);

	//fd 0 to 1
	rc = read(STDIN_FILENO, buf, 24);
	if (rc == -1)
		printf("%s\n", strerror(errno));
	buf[rc] = '\0';
	write(1, buf, rc);

	//fd 30 to 500
	rc = read(30, buf, 24);
	if (rc == -1)
		printf("%s\n", strerror(errno));
	buf[rc] = '\0';
	write(500, buf, rc);

	return 0;
}