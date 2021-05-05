#include "minishell.h"


/*
** 文字列がクォート中にあるかどうかを返す。
** 最初にクォートを検出したらinquoteをtrueへ変更、同じクォートが入力されるまでtrueを返す。
** 同じクォートが入力されたら、inquoteをfalseに更新、falseを返す。
** クォート以外の文字が入力されたら、現在のinquoteを返す。
*/

bool	is_inquote(char new_quote)
{
	static bool	inquote = false;
	static char	last_quote = 'i';

	if (!(new_quote == '"' || new_quote == '\''))
		return (inquote);
	if (inquote == false)
	{
		last_quote = new_quote;
		inquote = true;
		return (inquote);
	}
	if (last_quote == new_quote)
	{
		inquote = false;
		return (inquote);
	}
	return (inquote);
}