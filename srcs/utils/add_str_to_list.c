#include "minishell.h"

/*
**本当は返り値をboolにして、listに文字列を入れて返したいが
**なぜかNULLポインタが返ってしまう
**
**listがnullの場合　strのみが格納された二次元配列を返す
**strがnullの場合　listを返す
*/

char	**add_str_to_list(char **list, const char *str)
{
	size_t	i;
	char	*new_str;

	new_str = ft_strdup(str);
	if (new_str == NULL)
	{
		ft_free_split(list);
		return (NULL);
	}
	i = 0;
	while (list && list[i] != NULL)
		i++;
	list = (char **)ft_sprealloc(list, sizeof(char *) * (i + 2));
	if (list == NULL)
		return (NULL);
	list[i] = new_str;
	list[i + 1] = NULL;
	return (list);
}
