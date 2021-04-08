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

#define BUFFER_SIZE	2048

typedef enum	e_op {
	EOS,
	PIPELINE,
	SCOLON
}				t_op;

typedef enum	e_dir {
	PREV,
	NEXT
}				t_dir;

typedef struct	s_hist {
	struct s_hist	*next;
	struct s_hist	*prev;
	char			*line;
	char			*modified_line;
}				t_hist;

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
	char *ce;
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
void			sort_environ(char **a, char **b, size_t front, size_t end);
char			**get_sorted_environ();
int				print_sorted_env();

//parse
char			**tokenize(char *line);
bool			validate_line(char *line);
bool			validate_quote(char *line);
t_command		*get_commandline(char **list);
char			*get_laststr(char **list);
char			**get_strs(char **list, int len);
int				strschr(char **strs, char *set);
void			*wrap_free_commands_list(t_command *cmds);
bool			set_redirection_list(t_command *cmd, char **list);
char			*expand_envval(char *line);

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
void			sigint_handler(int signal);
void			sigquit_handler(int signal);


//builtin
int				execute_builtin(t_command *cmd);
int				execute_echo(t_command *cmd);
int				execute_env(t_command *cmd);
int				execute_unset(t_command *cmd);
int				execute_pwd(t_command *cmd);
int				execute_export(t_command *cmd);
int				execute_cd(t_command *cmd);
int				execute_exit(t_command *cmd);

//expander
char			*expand_envval(char *line);
char			*expand_exitstatus(char *ret, int *i);
char			*output_dollar(char *ret, int *i);
bool			preprocess_command(t_command *cmd);

//for debug
void			print_tcommand(t_command cmd);

//history
t_hist			*add_newelm_to_hist(t_hist *hist);
void			free_history(t_hist *history);
void			free_one_elm(t_hist *hist);
char			*display_history(char *line, char *c, int *i, t_hist **hist);
bool			update_history(char *line, t_hist **hist_p);

//error output
int				error_execute(char *path);
int				error_fork(void);
bool			redirect_error(char *key, char *errmsg);
bool			fd_error(long fd, char *errmsg);

//terminal setting and termcap
char			*read_line(t_hist **hist);
void			get_eof(char *line, t_hist **hist);
char			*get_sigint(char *line, char *c);
bool			set_terminal_setting(void);
bool			reset_terminal_setting(void);
bool			init_tterm(void);
bool			get_terminal_description(void);
bool			set_termcapsettings(t_termcap term);
char			*wrap_tgetstr(char *stored_cap, char *cap, char **bufaddr);
void			free_tterm(t_termcap term);

#endif
