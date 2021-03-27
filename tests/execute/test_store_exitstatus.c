#include "minishell.h"

int main(void)
{
	int status;


	status = store_exitstatus(1, 0);
	printf("%d\n", status);
	store_exitstatus(0, 1);
	status = store_exitstatus(1, 0);
	printf("%d\n", status);
	store_exitstatus(0, 255);
	status = store_exitstatus(1, 0);
	printf("%d\n", status);
	return 0;
}