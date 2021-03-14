#include "minishell.h"

/*
** main関数（仮）
*/
#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define MAGENTA	"\033[35m"
#define CYAN	"\033[36m"
#define WHITE	"\033[37m"
#define RESET	"\033[m"

static char *get_username()
{
	extern char **environ;
	char *username;

	while (*environ != NULL)
	{
		if (!ft_strncmp(*environ, "USER=", 5))
		{
			username = ft_substr(*environ, 5, ft_strlen(*environ) - 5);
			return (username);
		}
	}
	return (NULL);
}

int main(void)
{
	char *username;

	printf("this is color test.\n");
	printf("%sRED%s     %sGREEN%s\n", RED, RESET, GREEN, RESET);
	printf("%sYELLOW%s  %sBLUE%s\n", YELLOW, RESET, BLUE, RESET);
	printf("%sMAGENTA%s %sCYAN%s\n", MAGENTA, RESET, CYAN, RESET);
	printf("%sWHITE%s   RESET\n", WHITE, RESET);

	create_newenv();
	printf("Jenerating shell environment valiables ... %s[OK]%s\n", GREEN, RESET);
	username = get_username();
	printf("Hello %s, welcome to our minishell!\n", username);
	//prompt表示
	//call read_command
	return (0);
}
