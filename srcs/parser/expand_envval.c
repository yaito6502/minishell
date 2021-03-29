#include "minishell.h"

/*
** line中の展開が必要なdollarの数を返す。
*/

static int	has_dollar(char *line)
{
	int		ret;
	bool	inquote;

	ret = 0;
	puts(line);
	inquote = false;
	while (*line != '\0')
	{
		if (*line == '"')
		{
			if (inquote == false)
				inquote = true;
			else
				inquote = false;
		}
		if (*line == '\'' && inquote == false)
		{
			line++;
			while (*line != '\'')
				line++;
			line++;
		}
		if (*line == '$')
			ret++;
		line++;
	}
	return (ret);
}

static char	*copy_literal(char *line, char *ret, int *i)
{
	char *tmp;
	char *literal;

	*i = 1;
	while (line[*i] != '\'')
		(*i)++;
	literal = ft_substr(line, 0, *i + 1);
	if (literal == NULL)
		return (NULL);
	tmp = ret;
	ret = ft_strjoin(ret, literal);
	free(literal);
	if (ret == NULL)
		return (NULL);
	free(tmp);
	return (ret);
}

static char	*copy_normalchar(char *line, char *ret, int *i)
{
	char *tmp;
	char *str;

	*i = 0;
	while (line[*i] != '\'' && line[*i] != '\0' && line[*i] != '$')
		(*i)++;
	str = ft_substr(line, 0, *i);
	if (str == NULL)
		return (NULL);
	tmp = ret;
	ret = ft_strjoin(ret, str);
	free(str);
	if (ret == NULL)
		return (NULL);
	free(tmp);
	(*i)--;
	return (ret);
}

/*
** $?は特別な値、直前のコマンドの終了ステータス。別途保存用の関数を用意して、そこから値をとる。
*/

static char	*get_key(char *line, char *ret, int *i)
{
	char *tmp;
	char *name;
	char *env;

	*i = 0;
	line++;
	if (*line == '?')
		;//call store_exit_status()
	while (ft_isalnum(line[*i]) || line[*i] == '_')
		(*i)++;
	name = ft_substr(line, 0, *i);
	if (name == NULL)
		return (NULL);
	env = getenv(name);
	free(name);
	tmp = ret;
	ret = ft_strjoin(ret, env);
	if (ret == NULL)
		return (NULL);
	free(tmp);
	return (ret);
}

/*
** 入力から受け取った文字列を環境変数を展開した形で返す。
** ''中はリテラル、""中は展開
** ',"が二個ずつあることは別関数で確認する。（ない場合は、実装範囲外。エラー）
** 環境変数の命名規則はアルファベット,数字とアンダースコアの組み合わせとする。(要検証)
*/

char		*expand_envval(char *line)
{
	char	*ret;
	int		i;

	if (has_dollar(line) == 0)
		return (line);
	ret = NULL;
	while (*line != '\0')
	{
		if (*line == '\'')
			ret = copy_literal(line, ret, &i);
		else if (*line == '$')
			ret = get_key(line, ret, &i);
		else
			ret = copy_normalchar(line, ret, &i);
		if (ret == NULL)
			return (NULL);
		line = line + i + 1;
	}
	return (expand_envval(ret));
}
