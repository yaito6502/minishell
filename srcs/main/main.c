#include "minishell.h"

#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define MAGENTA	"\033[35m"
#define CYAN	"\033[36m"
#define WHITE	"\033[37m"
#define RESET	"\033[m"

static void	wait_command()
{
	char		*line;
	char		**tokens;
	t_command	*cmd;

	write(1, "\033[34mminishell\033[m > ",21);
	line = read_line();
	if (line == NULL)
		return ;
	//add_history(NULL, line);
	tokens = tokenize(line);
	cmd = get_commandline(tokens);
	start_commands(cmd);
	return ;
}

int main(void)
{
	extern t_termcap term;

	//printf("this is color test.\n");
	//printf("%sRED%s     %sGREEN%s\n", RED, RESET, GREEN, RESET);
	//printf("%sYELLOW%s  %sBLUE%s\n", YELLOW, RESET, BLUE, RESET);
	//printf("%sMAGENTA%s %sCYAN%s\n", MAGENTA, RESET, CYAN, RESET);
	//printf("%sWHITE%s   RESET\n", WHITE, RESET);

	create_newenv();
	init_tterm();
	get_terminal_description();
	set_termcapsettings(term);
	printf("Generating shell environment valiables ... %s[OK]%s\n", GREEN, RESET);
	printf("Hello, welcome to our minishell!\n");
	while(1)
		wait_command();
	return (0);
}
