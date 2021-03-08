
typedef enum e_op {
	EOS,
	PIPELINE,
	SCOLON
} t_op;

typedef struct s_command {
	struct s_command	*next;
	char				**argv;
	char				**redirect_in;
	char				**redirect_out;
	t_op				op;
	bool				receive_pipe;
	int					lastfd[2];
	int					pid;
} t_command;



typedef struct redirect {
	int		fd;
	char	*file;
}