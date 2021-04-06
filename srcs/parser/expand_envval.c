#include "minishell.h"

/*
** line中の展開が必要なdollarの数を返す。
*/

static int	has_dollar(char *line)
{
	int		ret;
	bool	inquote;

	ret = 0;
	inquote = false;
	while (*line != '\0')
	{
		if (*line == '"' && inquote == false)
			inquote = true;
		else if (*line == '"' && inquote == true)
			inquote = false;
		if (*line == '\'' && inquote == false)
		{
			line++;
			while (*line != '\'')
				line++;
			line++;
		}
		if (*line == '$' && *(line + 1) != '\0')
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
	free(tmp);
	return (ret);
}

static char	*copy_normalchar(char *line, char *ret, int *i, bool inquote)
{
	char *tmp;
	char *str;

	*i = 0;
	if (inquote == true)
		while (line[*i] != '\0' && line[*i] != '$')
			(*i)++;
	else
		while (line[*i] != '\'' && line[*i] != '\0' && line[*i] != '$')
			(*i)++;
	str = ft_substr(line, 0, *i);
	if (str == NULL)
		return (NULL);
	tmp = ret;
	ret = ft_strjoin(ret, str);
	free(str);
	free(tmp);
	(*i)--;
	return (ret);
}

/*
** $?は特別な値、直前のコマンドの終了ステータス。別途保存用の関数を用意して、そこから値をとる。
*/

static char	*get_key(char *line, char *ret, int *i)
{
	char	*tmp;
	char	*name;
	char	*env;

	*i = 0;
	line++;
	if (*line == '\0')
		return (output_dollar(ret, i));
	if (*line == '?')
		return (expand_exitstatus(ret, i));
	while (ft_isalnum(line[*i]) || line[*i] == '_')
		(*i)++;
	name = ft_substr(line, 0, *i);
	if (name == NULL)
		return (NULL);
	env = getenv(name);
	free(name);
	tmp = ret;
	ret = ft_strjoin(ret, env);
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
	bool	inquote;

	inquote = false;
	if (has_dollar(line) == 0)
		return (line);
	ret = NULL;
	while (*line != '\0')
	{
		if (*line == '"' && inquote == false)
			inquote = true;
		else if (*line == '"' && inquote == true)
			inquote = false;
		if (*line == '\'' && inquote == false)
			ret = copy_literal(line, ret, &i);
		else if (*line == '$')
			ret = get_key(line, ret, &i);
		else
			ret = copy_normalchar(line, ret, &i, inquote);
		if (ret == NULL)
			return (NULL);
		line = line + i + 1;
	}
	return (expand_envval(ret));
}
