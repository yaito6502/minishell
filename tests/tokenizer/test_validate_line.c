#include "minishell.h"

void output_ret(bool ret)
{
	if (ret)
		puts("line is valid.");
	else
		puts("line is invalid.");
}


int main(void)
{
	char	*line;
	bool	ret;

	line = ft_strdup("ls | grep;");
	ret = validate_line(line);
	output_ret(ret);
	free(line);

	line = ft_strdup("ls || grep history; ;");
	ret = validate_line(line);
	output_ret(ret);
	free(line);

	line = ft_strdup("ls ;; grep history;");
	ret = validate_line(line);
	output_ret(ret);
	free(line);

	line = ft_strdup("ls ; ; grep history;");
	ret = validate_line(line);
	output_ret(ret);
	free(line);

	line = ft_strdup("ls |; grep history;");
	ret = validate_line(line);
	output_ret(ret);
	free(line);

	line = ft_strdup("ls ; | grep history;");
	ret = validate_line(line);
	output_ret(ret);
	free(line);

	line = ft_strdup("ls & grep history;");
	ret = validate_line(line);
	output_ret(ret);
	free(line);

	line = ft_strdup("ls >");
	ret = validate_line(line);
	output_ret(ret);
	free(line);

	line = ft_strdup("ls >;");
	ret = validate_line(line);
	output_ret(ret);
	free(line);

	line = ft_strdup("ls |");
	ret = validate_line(line);
	output_ret(ret);
	free(line);

	line = ft_strdup("ls |;");
	ret = validate_line(line);
	output_ret(ret);
	free(line);

	line = ft_strdup("ls |&");
	ret = validate_line(line);
	output_ret(ret);
	free(line);

	line = ft_strdup("ls >>");
	ret = validate_line(line);
	output_ret(ret);
	free(line);

	line = ft_strdup("ls >>>>");
	ret = validate_line(line);
	output_ret(ret);
	free(line);

	line = ft_strdup("ls >>>");
	ret = validate_line(line);
	output_ret(ret);
	free(line);

	return 0;
}
