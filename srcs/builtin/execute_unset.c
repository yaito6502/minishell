#include "minishell.h"

/*
** unset関数、引数に与えらえれた文字列に該当するkeyの環境変数を削除する。
** 引数なし、keyに該当がないときは何もしない。終了ステータスはゼロ
** 複数引数がある場合、該当するkeyをすべて削除。
** return後、execute_builtin関数で、コマンド終了時の処理を呼び出す想定で実装します。
*/

void	error_unset(char *key, char *errmsg)
{
	ft_putstr_fd("bash: unset: `", STDERR_FILENO);
	ft_putstr_fd(key, STDERR_FILENO);
	ft_putendl_fd(errmsg, STDERR_FILENO);
	return ;
}

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
	free(environ[target_i]);
	i = 0;
	while (i < len - 1)
	{
		if (i == target_i)
		{
			env_p++;
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

int	execute_unset(t_command *cmd)
{
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	while (cmd->argv[i] != NULL)
	{
		if (!validate_envkey(cmd->argv[i]))
		{
			error_unset(cmd->argv[i], "': not a valid identifier");
			ret = 1;
		}
		else if (getenv(cmd->argv[i]))
		{
			if (!delete_key(cmd->argv[i]))
			{
				error_unset(cmd->argv[i], "':malloc error");
				ret = 1;
			}
		}
		i++;
	}
	return (ret);
}
