#include "minishell.h"

int main(int argc, char **argv)
{
	char *str;

	str = ft_strdup(argv[1]);
	if (validate_quote(str))
		puts("quote is closed.");
	else
		puts("line is not closed.");

	/*str = ft_strdup("'test' \"string.\"");
	puts(str);
	if (validate_quote(str))
		puts("quote is closed.");
	else
		puts("line is not closed.");

	str = ft_strdup("'t\"e\"s\"t' \"s'tring.\"");
	puts(str);
	if (validate_quote(str))
		puts("quote is closed.");
	else
		puts("line is not closed.");

	str = ft_strdup("'t\"e\"s\"t \"s'tring.\"");
	puts(str);
	if (validate_quote(str))
		puts("quote is closed.");
	else
		puts("line is not closed.");

	str = ft_strdup("'t\"e\"s\"t \"s'tring.\"\"");
	puts(str);
	if (validate_quote(str))
		puts("quote is closed.");
	else
		puts("line is not closed.");*/

	return (0);
}
