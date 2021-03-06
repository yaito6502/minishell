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

# define SAVE			0
# define LOAD			1
# define BUFFER_SIZE	2048

typedef enum e_op {
	EOS,
	PIPELINE,
	SCOLON
}	t_op;

typedef enum e_dir {
	PREV,
	NEXT
}	t_dir;

typedef struct s_hist {
	struct s_hist	*next;
	struct s_hist	*prev;
	char			*line;
	char			*modified_line;
}	t_hist;

typedef struct s_command {
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
}	t_command;

typedef struct s_termcap {
	char	*term_buf;
	char	*string_buf;
	char	*buf_ptr;
	int		pos[2];
	char	*cd;
	char	*dc;
	char	*up;
	char	*nd;
	char	*le;
	char	*cm;
}	t_termcap;

t_termcap	g_term;

//utils
t_command		*create_new_tcommand(void);
void			*free_commandslist(t_command **cmds);
int				is_builtin(t_command *cmds);
bool			create_newenv(void);
bool			add_newval_to_env(const char *str);
bool			has_slash(char *cmd);
char			**add_str_to_list(char **list, const char *str);
char			*read_command(void);
bool			validate_envkey(char *key);
bool			update_env(char *key, char *value);
void			sort_environ(char **a, char **b, size_t front, size_t end);
char			**get_sorted_environ(void);
int				print_sorted_env(void);
void			wrap_exit(unsigned int status);
char			*get_escapestr(char *line);
char			*add_path(char *path, char *dir);
char			*add_path_iterate(t_list *list);
bool			update_shlvl(void);
bool			is_inquote(char new_quote);

//parse
char			**tokenize(char *line);
bool			validate_line(char *line);
char			*get_first_sep(char *line);
bool			error_return(char *line, char last_op, bool has_space);
bool			validate_quote(char *line);
t_command		*parse(char **list);
t_command		*get_lastcommand(t_command *cmds);
char			**get_strs(char **list, int len);
int				strsncmp(char **strs, char *set);
bool			endswith(char *str, char *end);

//execute
char			*get_cmd_frompath(t_command *cmd);
bool			connect_pipeline(t_command *cmd, int newpipe[2]);
bool			do_redirection(t_command *cmd);
bool			reconnect_stdfd(int mode);
char			*get_cmd_frompath(t_command *cmd);
char			**cut_eachcolon(char *path);
char			*create_newpath(char *path);
int				execute_sequential(t_command *cmd);
int				execute_parallel(t_command *cmd);
void			start_commands(t_command *cmd);
int				store_exitstatus(int mode, int last_status);
void			sigint_handler(int signal);
void			sigquit_handler(int signal);
bool			is_dir(char *path);

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
void			get_envname(char *line, int *i);
bool			is_empty_env(char ***strs, char *line, int i);
char			*expand_firsttilde(char *arg);
char			*expand_exitstatus(char *ret, int *i);
char			*output_dollar(char *ret, int *i);
char			*trim_quote(char *arg);
bool			preprocess_command(t_command *cmd);
bool			validate_redirect(t_command *cmd);

//for debug
void			print_tcommand(t_command cmd);

//history
t_hist			*add_newelm_to_hist(t_hist *hist);
void			free_history(t_hist *history);
void			free_one_elm(t_hist *hist);
char			*display_history(char *line, char *c, int *i, t_hist **hist);
bool			update_history(char *line, t_hist **hist_p);

//error output
int				error_execute(char *path, int last_errno);
int				error_fork(void);
bool			redirect_error(char *key, char *errmsg);
bool			fd_error(long fd, char *errmsg);

//terminal setting and termcap
char			*read_line(t_hist **hist);
void			back_line(char *line, int *i);
void			get_eof(char *line, t_hist **hist);
char			*get_sigint(char *line, char *c);
bool			set_terminal_setting(void);
bool			reset_terminal_setting(void);
bool			init_tterm(void);
bool			get_terminal_description(void);
bool			set_termcapsettings(t_termcap g_term);
char			*wrap_tgetstr(char *stored_cap, char *cap);
void			free_tterm(t_termcap g_term);

bool			is_leftend(int *i);
void			get_cursor_position(int *row, int *col);

#endif
