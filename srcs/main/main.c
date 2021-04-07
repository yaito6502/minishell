#include "minishell.h"

#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define MAGENTA	"\033[35m"
#define CYAN	"\033[36m"
#define WHITE	"\033[37m"
#define RESET	"\033[m"

static void	wait_command(t_hist **hist)
{
	char		*line;
	char		*tmp;
	char		**tokens;
	t_command	*cmd;

	write(STDOUT_FILENO, "\033[34mminishell\033[m > ",21);
	*hist = add_newelm_to_hist(*hist);
	line = read_line(hist);
	tmp = line;
	line = ft_strtrim(line, "\v\r\f\t\n ");
	free(tmp);
	if (line == NULL)
		return ;
	tokens = tokenize(line);
	free(line);
	if (tokens == NULL)
		return ;
	cmd = get_commandline(tokens);
	ft_free_split(tokens);
	if (cmd == NULL)
		return ;
	start_commands(cmd);
	free_commandslist(&cmd);
	return ;
}

int main(void)
{
	extern t_termcap	term;
	t_hist				*hist;

	hist = NULL;
	create_newenv();
	init_tterm();
	get_terminal_description();
	set_termcapsettings(term);
	printf("Generating shell environment variables ... %s[OK]%s\n", GREEN, RESET);
	printf("Hello, welcome to our minishell!\n");
	while(1)
		wait_command(&hist);
	return (0);
}
