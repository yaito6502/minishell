#include "minishell.h"

void output_ret(bool ret)
{
	if (ret)
		puts("line is valid.");
	else
		puts("line is invalid.");
}

bool test_line(char *line, char *expected)
{
	printf("input : [%s]\n", line);
	printf("expected : %s\n", expected);
	return (validate_line(line));
}

int main(void)
{
	bool	ret;

	ret = test_line(";>a", "syntax error near unexpected token `;'");
	output_ret(ret);

	ret = test_line("ls >>", "syntax error near unexpected token `newline'");
	output_ret(ret);

	ret = test_line("ls >>>>", "syntax error near unexpected token `>>'");
	output_ret(ret);

	ret = test_line("ls >>>", "syntax error near unexpected token `>'");
	output_ret(ret);

	ret = test_line("ls || grep history; ;", "syntax error near unexpected token `||'");
	output_ret(ret);

	ret = test_line("ls ;; grep history;", "syntax error near unexpected token `;;'");
	output_ret(ret);

	ret = test_line("ls ; ; grep history;", "syntax error near unexpected token `;'");
	output_ret(ret);

	ret = test_line("ls |; grep history;", "syntax error near unexpected token `;'");
	output_ret(ret);

	ret = test_line("ls ; | grep history;", "syntax error near unexpected token `|'");
	output_ret(ret);

	ret = test_line("ls & grep history;", "syntax error near unexpected token `&'");
	output_ret(ret);

	ret = test_line("ls >", "syntax error near unexpected token `newline'");
	output_ret(ret);

	ret = test_line("ls >;", "syntax error near unexpected token `;'");
	output_ret(ret);

	ret = test_line("ls |", "syntax error near unexpected token `newline'");
	output_ret(ret);

	ret = test_line("ls |;", "syntax error near unexpected token `;'");
	output_ret(ret);

	ret = test_line("ls |&", "syntax error near unexpected token `&'");
	output_ret(ret);

	return 0;
}
