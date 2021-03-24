#include "minishell.h"

/*
**ft_split、ft_split_multiの強化版です。
**set[0]に区切り文字を
**set[1]に挿入文字を入れて使用します
**下の例のように動作します。
**
**例：	 *line = "hello : 42: Tokyo!:"
**		*set[2] = {" \t\n\v\f\r", ":!"};
**
**		split_line(line, set);
**
**		**strs = {"hello", ":", "42", ":", "Tokyo", "!", ":", NULL};
*/

static int		is_sep(char str, char *set)
{
	while (*set != '\0')
	{
		if (str == *set)
			return (1);
		set++;
	}
	return (0);
}

static int		check_str(char *str, char *set[2])
{
	int w;

	w = 0;
	while (*str)
	{
		if (is_sep(*str, set[1]))
		{
			w++;
			str++;
			continue;
		}
		if (is_sep(*str, set[0]))
		{
			str++;
			continue;
		}
		w++;
		while (*str && !is_sep(*str, set[0]) && !is_sep(*str, set[1]))
			str++;
	}
	return (w);
}

static char		**split_wrd(char **ret, char *str, char *set[2], int wrds)
{
	int		i;
	int		l;

	i = 0;
	while (i < wrds)
	{
		while (is_sep(*str, set[0]))
			str++;
		l = 0;
		if (str[l] && is_sep(str[l], set[1]))
			l++;
		else
			while (str[l] && !is_sep(str[l], set[1]) && !is_sep(str[l], set[0]))
				l++;
		ret[i] = malloc(sizeof(char) * (l + 1));
		if (!ret[i])
		{
			while (i >= 0)
				free(ret[i--]);
			return (NULL);
		}
		ft_strlcpy(ret[i++], str, l + 1);
		str = str + l;
	}
	return (ret);
}

char			**split_line(char *str, char *set[2])
{
	char	**ret;
	int		wrds;

	if (!str || !set)
		return (NULL);
	wrds = check_str(str, set);
	printf("size[%d]\n", wrds);
	if (!(ret = (char **)malloc(sizeof(*ret) * (wrds + 1))))
		return (NULL);
	ret[wrds] = NULL;
	if (!split_wrd(ret, str, set, wrds))
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}
