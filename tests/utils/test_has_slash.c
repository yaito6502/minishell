#include "minishell.h"

int main(void)
{
	char *str;
	bool ret;

	str = ft_strdup("/usr/local/bin");
	ret = has_slash(str);
	if (ret == true)
		puts("this string has slash");
	else
		puts("there is no slash");

	str = ft_strdup("usrlocalbin");
	ret = has_slash(str);
	if (ret == true)
		puts("this string has slash");
	else
		puts("there is no slash");
	return 0;
}