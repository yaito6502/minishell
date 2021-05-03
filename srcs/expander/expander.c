#include "minishell.h"

/*
** cmd.argv内の文字列に対して環境変数展開、"'の削除を行う関数。
** クォート中のクォートはリテラルとして扱う。
*/
#define SPACES	"\v\r\f\t\n "

static bool	is_args(char *str)
{
	int		len;
	int		i;
	char	*dollar;
	char	*name;

	dollar = ft_strchr(str, '$');
	if (!dollar)
		return (false);
	len = dollar - str;
	get_envname(dollar + 1, &len);
	name = ft_substr(dollar, 1, len);
	dollar = getenv(name);
	free(name);
	if (!dollar)
		return (false);
	i = 0;
	while (dollar[i] && !ft_strchr(SPACES, dollar[i]))
		i++;
	return (dollar[i]);
}

static char	*get_preformatted_tokens(char *token)
{
	char	*expded;
	char	*escaped;
	char	*preformetted;

	expded = expand_firsttilde(token);
	escaped = get_escapestr(expded);
	preformetted = trim_quote(escaped);
	free(expded);
	free(escaped);
	return (preformetted);
}

static bool	insert_expded_args(char ***strs, int index)
{
	char	**tokens;
	char	**new_strs;
	int		j;

	new_strs = NULL;
	if (index > 0)
		new_strs = get_strs(*strs, index);
	tokens = ft_split_multi((*strs)[index], SPACES);
	if ((!new_strs && index > 0) || !tokens)
	{
		ft_free_split(tokens);
		return (ft_free_split(*strs));
	}
	j = 1;
	new_strs = add_str_to_list(new_strs, tokens[0]);
	while (tokens[j] && new_strs)
		new_strs = add_str_to_list(new_strs, tokens[j++]);
	ft_free_split(tokens);
	while ((*strs)[++index] && new_strs)
		new_strs = add_str_to_list(new_strs, (*strs)[index++]);
	ft_free_split(*strs);
	*strs = new_strs;
	return (*strs);
}

static bool	preprocess_tokens(char ***strs)
{
	int		i;
	char	*expded;
	char	*ret;
	bool	is_arg;

	i = 0;
	while ((*strs) != NULL && (*strs)[i] != NULL)
	{
		is_arg = is_args((*strs)[i]);
		expded = expand_envval((*strs)[i]);
		if (expded == (*strs)[i])
			expded = ft_strdup((*strs)[i]);
		if (is_empty_env(strs, expded, i))
			continue ;
		ret = get_preformatted_tokens(expded);
		free(expded);
		if (ret == NULL)
			return (false);
		free((*strs)[i]);
		(*strs)[i] = ret;
		if (is_arg && !insert_expded_args(strs, i))
			return (false);
		i++;
	}
	return (true);
}

bool	preprocess_command(t_command *cmd)
{
	if (!preprocess_tokens(&cmd->argv)
		|| !preprocess_tokens(&cmd->redirect_in)
		|| !preprocess_tokens(&cmd->redirect_out))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (false);
	}
	return (true);
}
