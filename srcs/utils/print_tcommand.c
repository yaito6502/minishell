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
		printf("%s, ",str[i]);
		i++;
	}
	printf("\n");
}

void	print_tcommand(t_command cmd)
{
	printf("next        : ");
	printf("%p\n", cmd.next);
	printf("argv        : ");
	print_splits(cmd.argv);
	printf("redirect_in : ");
	print_splits(cmd.redirect_in);
	printf("redirect_out: ");
	print_splits(cmd.redirect_out);
	printf("receive_pipe: ");
	if (cmd.receive_pipe == true)
		printf("True\n");
	else
		printf("False\n");
	printf("lastfd[]    : ");
	printf("{%d,%d}\n", cmd.lastfd[0], cmd.lastfd[1]);
	printf("pid         : ");
	printf("%d\n", cmd.pid);
	printf("op          : ");
	if (cmd.op == EOS)
		printf("EOS\n");
	if (cmd.op == SCOLON)
		printf("SCOLON\n");
	if (cmd.op == PIPELINE)
		printf("PIPELINE\n");
}
