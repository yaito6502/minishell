#include "minishell.h"

/*
** 標準入力から受け取った、lineをトークン化した二次元配列にする関数。
** e.g. $A "world, $USER" 3>outfile1| ls $HOME;
** -> {{$A}, {"world, $USER"}, {3>}, {outfile1}, {|}, {ls}, {$HOME}, {;}, NULL}
** errorの時はNULL、それ以外は、作成したtoken配列を返す。
*/

/*
** 現在読み込んだindexまでがクォート中にあるかないかを返す。
*/

static bool		is_inquote(char *p, int len)
{
	int		quote_count;
	int		i;
	int		j;
	char	quote;

	i = 0;
	while (p[i] != '\0' && i < len)
	{
		if (p[i] == '\'' || p[i] == '"')
		{
			quote = p[i];
			j = 1;
			while (i + j < len && p[i + j] != quote)
				j++;
			if (i + j == len)
				return (true);
			i += j;
		}
		i++;
	}
	return (false);
}

/*
** スペース区切り文字を見つけてインデックスを返す。"'の中身はそのまま渡す。
*/

static int		get_index(char *p)
{
	int		i;

	i = 0;
	while (p[i] != '\0')
	{
		while (p[i] != '\0' && !ft_strchr(" |><;", p[i]))
			i++;
		if (is_inquote(p, i))
		{
			while (p[i] != '\0' && !ft_strchr("\"'", p[i]))
				i++;
			i++;
		}
		else
			return (i);
	}
	return (i);
}

/*
** <>が来たとき前のトークンが数字のみor>が連続するときの場合結合する。
*/

static char		**check_lasttoken(char **tokens, char *op)
{
	int		i;
	int		j;
	char	*tmp;

	if (op == NULL)
		return (NULL);
	i = 0;
	while (tokens[i] != NULL)
		i++;
	i -= 1;
	j = 0;
	while (ft_isdigit(tokens[i][j]))
		j++;
	if (tokens[i][j] == '\0' || \
	(ft_strchr("<>", tokens[i][j]) && tokens[i][j + 1] == '\0'))
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
	tmp = ft_substr(p, 0, 1);
	if (tmp == NULL)
		return (NULL);
	if (*p == '>' || *p == '<')
		*tokens = check_lasttoken(*tokens, tmp);
	else
		*tokens = add_str_to_list(*tokens, tmp);
	free(tmp);
	if (*tokens == NULL)
		return (NULL);
	return (p + 1);
}

char			**tokenize(char *line)
{
	int		i;
	char	**tokens;
	char	*tmp;

	tokens = NULL;
	while (*line != '\0')
	{
		i = get_index(line);
		if (i > 0)
		{
			tmp = ft_substr(line, 0, i);
			if (tmp == NULL)
				return (NULL);
			tokens = add_str_to_list(tokens, tmp);
			free(tmp);
			line += i;
		}
		else
			line = put_op_token(&tokens, line);
		if (tokens == NULL || line == NULL)
			return (NULL);
	}
	return (tokens);
}
