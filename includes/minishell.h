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

# define SAVE 0
# define LOAD 1

typedef enum	e_op {
	EOS,
	PIPELINE,
	SCOLON
}				t_op;

typedef enum	e_dir {
	PREV,
	NEXT
}				t_dir;

typedef struct	s_history {
	struct s_history	*next;
	struct s_history	*prev;
	char				*line;
}				t_history;

typedef struct	s_command {
	struct s_command	*next;
	char				**argv;
	char				**redirect_in;
	char				**redirect_out;
	t_op				op;
	bool				receive_pipe;
	int					lastfd[2];
	bool				has_childproc;
	pid_t				pid;
	int					exitstatus;
}				t_command;

typedef struct	s_termcap {
	char *term_buf;
	char *string_buf;
	char *buf_ptr;
	char *dc;
	char *DC;
	char *le;
}				t_termcap;

t_termcap term;

//utils
t_command		*create_new_tcommand(void);
void			free_commandslist(t_command **cmds);
int				is_builtin(t_command *cmds);
bool			create_newenv(void);
bool			add_newval_to_env(const char *str);
bool			has_slash(char *cmd);
char			**add_str_to_list(char **list, const char *str);
char			*read_command(void);
char			**split_line(char *str, char *set[2]);
bool			validate_envkey(char *key);
bool			update_env(char *key, char *value);

//parse
char			**tokenize(char *line);
bool			validate_line(char *line);
t_command		*get_commandline(char **list);
char			*get_laststr(char **list);
char			**get_strs(char **list, int len);
int				strschr(char **strs, char *set);
void			*wrap_free_commands_list(t_command *cmds);
bool			set_redirection_list(t_command *cmd, char **list);

//execute
char			*get_cmd_frompath(t_command *cmd);
bool			connect_pipeline(t_command *cmd, int newpipe[2]);
bool			do_redirection(t_command *cmd);
bool			reconnect_stdfd(int mode);
char			*get_cmd_frompath(t_command *cmd);
char			*join_path(char *cmd);
int				execute_sequential(t_command *cmd);
int				execute_parallel(t_command *cmd);
void			start_commands(t_command *cmd);
int				store_exitstatus(int mode, int last_status);
char			*read_line(void);

//builtin
int				execute_builtin(t_command *cmd);
int				execute_echo(t_command *cmd);
int				execute_env(t_command *cmd);
int				execute_unset(t_command *cmd);
int				execute_pwd(t_command *cmd);
int				execute_exit(t_command *cmd);

//parser
char			*expand_envval(char *line);
bool			preprocess_command(t_command *cmd);
char			**tokenize(char *line);

//for debug
void			print_tcommand(t_command cmd);

//history
t_history		*add_history(t_history *last_history, char *line);
void			free_history(t_history *history);

//error output
int				error_execute(char *path);
int				error_fork(void);
bool			redirect_error(char *key, char *errmsg);
bool			fd_error(long fd, char *errmsg);

//terminal setting and termcap
char			*read_line(void);
bool			set_terminal_setting(void);
bool			reset_terminal_setting(void);
bool			init_tterm(void);
bool			get_terminal_description(void);
bool			set_termcapsettings(t_termcap term);
char			*wrap_tgetstr(char *stored_cap, char *cap, char **bufaddr);
void			free_tterm(t_termcap term);
int				ft_putchar(int n);

#endif
