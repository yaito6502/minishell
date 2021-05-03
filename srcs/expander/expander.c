#include "minishell.h"

/*
** cmd.argv内の文字列に対して環境変数展開、"'の削除を行う関数。
** クォート中のクォートはリテラルとして扱う。
*/

static int	get_len(char *line)
{
	int		i;
	int		len;
	char	quote;

	i = 0;
	len = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '\'' && line[i] != '"')
		{
			len++;
			i++;
			continue ;
		}
		quote = line[i];
		i++;
		while (line[i] != '\0' && line[i] != quote)
		{
			len++;
			i++;
		}
		i++;
	}
	return (len);
}

static char	*copy_literal(char *arg, char *tmp, int *i)
{
	char	quote;

	quote = arg[*i];
	(*i)++;
	while (arg[*i] != quote)
	{
		*tmp = arg[*i];
		tmp++;
		(*i)++;
	}
	(*i)++;
	return (tmp);
}

static char	*trim_quote(char *arg)
{
	int		i;
	char	*tmp;
	char	*ret;

	if (arg == NULL)
		return (NULL);
	tmp = malloc(sizeof(char) * (get_len(arg) + 1));
	if (tmp == NULL)
		return (NULL);
	i = 0;
	ret = tmp;
	while (arg[i] != '\0')
	{
		if (arg[i] == '\'' || arg[i] == '"')
		{
			tmp = copy_literal(arg, tmp, &i);
			continue ;
		}
		*tmp++ = arg[i];
		i++;
	}
	*tmp = '\0';
	return (ret);
}

static bool	preprocess_tokens(char ***strs)
{
	int		i;
	char	*ret[4];

	i = 0;
	while ((*strs) != NULL && (*strs)[i] != NULL)
	{
		ret[0] = expand_envval((*strs)[i]);
		if (ret[0] == (*strs)[i])
			ret[0] = ft_strdup((*strs)[i]);
		if (is_empty_env(strs, ret[0], i))
			continue ;
		ret[1] = expand_firsttilde(ret[0]);
		ret[2] = get_escapestr(ret[1]);
		ret[3] = trim_quote(ret[2]);
		free(ret[0]);
		free(ret[1]);
		free(ret[2]);
		if (ret[3] == NULL)
			return (false);
		free((*strs)[i]);
		(*strs)[i] = ret[3];
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
