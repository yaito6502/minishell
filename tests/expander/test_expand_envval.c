#include "minishell.h"

int main(void)
{
	char *str;
	char *ret;
	// export TEST="$TERM + $PWD"

	//str = ft_strdup("echo \" $12USER\"'$PWD'");
	//str = ft_strdup("''''''''''$USER''''''''''");
	str = ft_strdup("\"'$USER'\"'$USER'");
	//str = ft_strdup("$$$");
	puts(str);
	ret = expand_envval(str);
	puts(ret);
	free(str);
	free(ret);
	return 0;
}