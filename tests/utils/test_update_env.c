#include "minishell.h"

int		main(int argc, char **argv)
{
	bool status;

	status = update_env(argv[1], argv[2]);
	if (status)
		printf("%s=%s\n", argv[1], getenv(argv[1]));
	else
		puts("false");
	//system("leaks test");
	return (0);
}
