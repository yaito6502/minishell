#include "minishell.h"

int main(void)
{
	t_command *cmd;
	int rc;
	char buf[25];
	int fd;

	cmd = create_new_tcommand();
	cmd->redirect_in = ft_split("./testinout/infile1,./testinout/infile2",',');
	cmd->redirect_out = ft_split(">,testinout/outfile1,500>,testinout/outfile500",',');
	print_tcommand(*cmd);
	redirect_input(cmd);
	redirect_output(cmd);

	rc = read(STDIN_FILENO, buf, 24);
	if (rc == -1)
		printf("%s\n", strerror(errno));
	buf[rc] = '\0';
	write(500, buf, rc);
}