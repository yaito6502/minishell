#include "minishell.h"

/*
** 標準入力から受け取った、lineをトークン化した二次元配列にする関数。
** e.g. $A "world, $USER" 3>outfile1| ls $HOME;
** -> {{$A}, {"world, $USER"}, {3>}, {outfile1}, {|}, {ls}, {$HOME}, {;}, NULL}
** errorの時はNULL、それ以外は、作成したtoken配列を返す。
*/

/*
** スペース区切り文字を見つけてインデックスを返す。"'の中身はそのまま渡す。
*/

static int		get_index(char *p)
{
	int		i;
	int		j;
	int		c;

	i = 0;
	j = 0;
	c = 0;
	while (p[i] != '\0' && !ft_strchr(" |><;", p[i]))
		i++;
	while (j < i)
	{
		if (ft_strchr("\"'",p[j]))
			c++;
		j++;
	}
	if (c % 2 == 1)
	{
		while (p[i] != '\0' && !ft_strchr("\"'", p[i]))
			i++;
		i++;
	}
	return (i);
}

/*
** <>が来たとき前のトークンが数字のみor>が連続するときの場合結合する。
*/
//>>未対応
static char		**check_lasttoken(char **tokens, char *op)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (tokens[i] != NULL)
		i++;
	i -= 1;
	j = 0;
	while (ft_isdigit(tokens[i][j]))
		j++;
	if (tokens[i][j] == '\0')
	{
		tmp = tokens[i];
		tokens[i] = ft_strjoin(tokens[i], op);
		free(tmp);
		return (tokens);
	}
	tokens = add_str_to_list(tokens, op);
	return (tokens);
}

static char		*put_op_token(char ***tokens, char *p)
{
	char *tmp;

	if (*p == ' ')
	{
		while (*p == ' ')
			p++;
		return (p);
	}
	if (*p == '>' || *p == '<')
	{
		*tokens = check_lasttoken(*tokens, ft_substr(p, 0, 1));
	}
	else
		*tokens = add_str_to_list(*tokens, ft_substr(p, 0, 1));
	if (*tokens == NULL)
		return (NULL);
	return (p + 1);
}

char			**tokenize(char *line)
{
	int		i;
	char	*p;
	char	**tokens;

	tokens = NULL;
	p = line;
	while(*p != '\0')
	{
		i = get_index(p);
		if (i > 0)
		{
			tokens = add_str_to_list(tokens, ft_substr(p, 0, i));
			if (tokens == NULL)
				return (NULL);
			p += i;
		}
		else
		{
			p = put_op_token(&tokens, p);
			if (p == NULL)
				return (NULL);
		}
	}
	return (tokens);
}