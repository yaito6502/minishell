#include "minishell.h"

/*
** unset関数、引数に与えらえれた文字列に該当するkeyの環境変数を削除する。
** 引数なし、keyに該当がないときは何もしない。終了ステータスはゼロ
** 複数引数がある場合、該当するkeyをすべて削除。
** return後、execute_builtin関数で、コマンド終了時の処理を呼び出す想定で実装します。
*/

static int	get_target_index(char *key)
{
	int			i;
	int			len;
	extern char	**environ;

	i = 0;
	while (environ[i] != NULL)
	{
		len = ft_strlen(key);
		if (!ft_strncmp(key, environ[i], len) && environ[i][len] == '=')
			break ;
		i++;
	}
	return (i);
}

static void	copy_environ(char **new_env, int target_i, int len)
{
	extern char	**environ;
	char		**env_p;
	int			i;

	env_p = environ;
	i = 0;
	while (i < len - 1)
	{
		if (i == target_i)
		{
			env_p++;
			free(environ[i]);
			target_i = -1;
			continue ;
		}
		new_env[i] = *env_p;
		i++;
		env_p++;
	}
	new_env[len - 1] = NULL;
	free(environ);
	environ = new_env;
	return ;
}

static bool	delete_key(char *key)
{
	extern char	**environ;
	int			target_i;
	int			len;
	char		**new_env;

	len = 0;
	while (environ[len] != NULL)
		len++;
	new_env = (char **)malloc(len * sizeof(char *));
	if (new_env == NULL)
		return (false);
	target_i = get_target_index(key);
	copy_environ(new_env, target_i, len);
	return (true);
}

void		execute_unset(t_command *cmd)
{
	int		i;
	char	*env;
	bool	ret;

	i = 1;
	while (cmd->argv[i] != NULL)
	{
		env = getenv(cmd->argv[i]);
		if (env == NULL)
		{
			i++;
			continue ;
		}
		ret = delete_key(cmd->argv[i]);
		if (ret == false)
			return ;//error
		i++;
	}
	return ;
}
