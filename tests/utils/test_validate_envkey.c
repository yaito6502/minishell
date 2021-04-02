#include "minishell.h"

void	print_ret(bool ret)
{
	if (ret == true)
		puts("true");
	else
		puts("false");
	return ;
}

int		main(void)
{
	bool	ret;

	ret = validate_envkey("test_123");
	print_ret(ret);
	ret = validate_envkey("12_test");
	print_ret(ret);
	ret = validate_envkey("_1231ASD");
	print_ret(ret);
	return 0;
}