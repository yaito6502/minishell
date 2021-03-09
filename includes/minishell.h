#ifndef MINISHELL_H
# define MINISHELL_H

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


//execute
void		start_commands(t_command *cmds);
void		execute_parallel(t_command *cmds);
void		execute_sequential(t_command *cmds);
void		send_pipeline(t_command *cmds, int newpipe[2]);
void		receive_pipeline(t_command *cmds);
void		redirect_input(t_command *cmds);
void		redirect_output(t_command *cmds);

//utils
int			is_builtin(t_command *cmds);
void		free_commandslist(t_command **cmds);

#endif
