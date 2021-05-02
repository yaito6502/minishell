#include "minishell.h"

#define RED		"\033[31m"
#define GREEN	"\033[32m"
#define YELLOW	"\033[33m"
#define BLUE	"\033[34m"
#define MAGENTA	"\033[35m"
#define CYAN	"\033[36m"
#define WHITE	"\033[37m"
#define RESET	"\033[m"
#define SPACES	"\v\r\f\t\n "

static char	*check_validline(char *line)
{
	char	*tmp;

	if (!line)
		return (NULL);
	tmp = ft_strtrim(line, SPACES);
	if (tmp == NULL)
		return (NULL);
	if (!validate_line(tmp) || !validate_quote(tmp))
	{
		free(tmp);
		free(line);
		return (NULL);
	}
	free(line);
	line = tmp;
	return (line);
}

static void	wait_command(t_hist **hist)
{
	char		*line;
	char		**tokens;
	t_command	*cmd;

	write(STDERR_FILENO, "\033[34mminishell\033[m > ", 21);
	*hist = add_newelm_to_hist(*hist);
	line = read_line(hist);
	line = check_validline(line);
	if (line == NULL)
		return ;
	tokens = tokenize(line);
	free(line);
	cmd = parse(tokens);
	ft_free_split(tokens);
	if (cmd == NULL)
		return ;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	start_commands(cmd);
	free_commandslist(&cmd);
	return ;
}

static void	run_command(char *line)
{
	char		**tokens;
	t_command	*cmd;

	line = check_validline(line);
	if (line == NULL)
		exit(2);
	tokens = tokenize(line);
	free(line);
	cmd = parse(tokens);
	ft_free_split(tokens);
	if (cmd == NULL)
		exit(EXIT_FAILURE);
	start_commands(cmd);
	free_commandslist(&cmd);
	exit(store_exitstatus(LOAD, 0));
}

int	main(int argc, char **argv)
{
	extern t_termcap	term;
	t_hist				*hist;
	char				*line;

	hist = NULL;
	create_newenv();
	init_tterm();
	if (!update_shlvl())
		wrap_exit(EXIT_FAILURE);
	if (argc > 2 && !ft_strncmp(argv[1], "-c", 3))
	{
		line = ft_strdup(argv[2]);
		run_command(line);
	}
	if (!isatty(STDIN_FILENO))
	{
		line = read_command();
		run_command(line);
	}
	get_terminal_description();
	set_termcapsettings(term);
	while (1)
		wait_command(&hist);
	return (0);
}
