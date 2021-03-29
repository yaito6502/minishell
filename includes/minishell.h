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
# include <termios.h>
# include <termcap.h>

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
bool		has_slash(char *cmd);
char		**add_str_to_list(char **list, const char *str);
char		*read_command(void);
char		**split_line(char *str, char *set[2]);

//parse
t_command	*get_commandline(char **list);
char		*get_laststr(char **list);
char		**get_strs(char **list, int len);
int			strschr(char **strs, char *set);
void		*wrap_free_commands_list(t_command *cmds);
bool		set_redirection_list(t_command *cmd, char **list);

//execute
char		*get_cmd_frompath(t_command *cmd);
void		send_pipeline(t_command *cmds, int newpipe[2]);
void		receive_pipeline(t_command *cmds);
void		redirect_input(t_command *cmds);
void		redirect_output(t_command *cmds);
bool		reconnect_stdfd(int mode);
char		*get_cmd_frompath(t_command *cmd);
char		*join_path(char *cmd);
void		execute_sequential(t_command *cmd);
void		execute_parallel(t_command *cmd);
void		start_commands(t_command *cmd);

//builtin
void		execute_env(t_command *cmd);
void		execute_unset(t_command *cmd);
void		execute_echo(t_command *cmd);
int			execute_pwd(t_command *cmd);

//for debug
void		print_tcommand(t_command cmd);

char		**tokenize(char *line);
char		*read_line(void);
bool		set_terminal_setting(void);
bool		reset_terminal_setting(void);

#endif
