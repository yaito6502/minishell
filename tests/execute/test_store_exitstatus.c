#include "minishell.h"

int main(void)
{
	int status;


	status = store_exitstatus(LOAD, 0);
	printf("%d\n", status);
	store_exitstatus(SAVE, 1);
	status = store_exitstatus(LOAD, 0);
	printf("%d\n", status);
	store_exitstatus(SAVE, 255);
	status = store_exitstatus(LOAD, 0);
	printf("%d\n", status);
	return 0;
}
