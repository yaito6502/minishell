#include "minishell.h"

char	*expand_exitstatus(char *ret, int *i)
{
	char	*status;
	char	*tmp;

	*i = 1;
	status = ft_itoa(store_exitstatus(LOAD, 0));
	if (status == NULL)
		return (NULL);
	tmp = ret;
	ret = ft_strjoin(ret, status);
	free(status);
	free(tmp);
	return (ret);
}