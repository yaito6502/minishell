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
			quote = line[i];
			while ()
			len++;
		}
		i++;
	}
	return (len);
}

static char	*trim_quote(char *arg)
{
	int	i;
	int	j;
	char	*ret;

	if (arg == NULL)
		return (NULL);
	ret = malloc(sizeof(char) * get_len(arg));
	if (ret == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '\'' || arg[i] == '"')
		{
			i++;
			continue ;
		}
		ret[j] = arg[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

bool	preprocess_command(t_command *cmd)
{
	int		i;
	char	*ret;

	i = 0;
	while (cmd->argv[i] != NULL)
	{
		ret = expand_envval(cmd->argv[i]);
		ret = trim_quote(ret);
		if (ret == NULL)
			return (false);
		free(cmd->argv[i]);
		cmd->argv[i] = ret;
		i++;
	}
	return (true);
}