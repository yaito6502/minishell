#include "minishell.h"

int main(void)
{
	int fd;
	int rc;
	char buf[25];
	bool ret;

	ret = reconnect_stdfd(0);
	if (ret == true)
		printf("standard fd duplication is complete.\n");
	else
		printf("something wrong.\n");
	fd = open("./testinout/infile1", O_RDWR);
	dup2(fd, STDIN_FILENO);
	fd = open("./testinout/outfile", O_RDWR | O_CREAT, S_IRWXU);
	dup2(fd, STDOUT_FILENO);
	rc = read(STDIN_FILENO, buf, 24);
	buf[rc] = '\0';
	write(STDOUT_FILENO, buf, rc);

	ret = reconnect_stdfd(1);
	if (ret == true)
		printf("standard fd restore is complete.\n");
	else
		printf("something wrong.\n");
	rc = read(STDIN_FILENO, buf, 24);
	buf[rc] = '\0';
	write(STDOUT_FILENO, buf, rc);
	return 0;
}