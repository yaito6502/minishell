#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <string.h>

typedef enum	e_op{
	EOS,
	PIPELINE,
	SCOLON
}				t_op;

typedef struct	s_command {
	struct s_command	*next;
	char				**argv;
	char				**redirect_in;
	char				**redirect_out;
	t_op				op;
	bool				receive_pipe;
	int					lastfd[2];
	int					pid;
}				t_command;


//utils
t_command	*create_new_tcommand(void);
void		free_commandslist(t_command **cmds);
int			is_builtin(t_command *cmds);
bool		create_newenv(void);
bool		add_newval_to_env(const char *str);

//execute
char		*get_cmd_frompath(t_command *cmd);
void		send_pipeline(t_command *cmds, int newpipe[2]);
void		receive_pipeline(t_command *cmds);
void		redirect_input(t_command *cmds);
void		redirect_output(t_command *cmds);
char		*get_cmd_frompath(t_command *cmd);
void		execute_sequential(t_command *cmd);

//parser
char		*expand_envval(char *line);

//for debug
void		print_tcommand(t_command cmd);

#endif
