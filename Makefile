NAME = minishell

CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes -I.

LIBFT = ./libft/libft.a

SRCFILE =	srcs/main/main.c \
			srcs/utils/create_new_tcommand.c \
			srcs/utils/free_commandslist.c \
			srcs/utils/is_builtin.c \
			srcs/utils/create_newenv.c \
			srcs/utils/add_newval_to_env.c \
			srcs/utils/has_slash.c \
			srcs/utils/add_str_to_list.c \
			srcs/utils/split_line.c \
			srcs/parser/parser.c \
			srcs/parser/parser_utils.c \
			srcs/execute/connect_pipeline.c \
			srcs/execute/do_redirection.c \
			srcs/execute/get_cmd_frompath.c \
			srcs/execute/join_path.c \
			srcs/execute/reconnect_stdfd.c \
			srcs/execute/execute_sequential.c \
			srcs/execute/execute_parallel.c \
			srcs/execute/start_commands.c \
			srcs/execute/read_command.c \
			srcs/builtin/execute_env.c \
			srcs/builtin/execute_unset.c \
			srcs/builtin/execute_pwd.c \
			srcs/builtin/execute_echo.c \
			srcs/builtin/execute_cd.c \
			srcs/tokenizer/tokenize.c


TESTFILE =	tests/print_tcommand.c \
			tests/utils/test_create_new_tcommand.c \
			tests/utils/test_free_commandslist.c \
			tests/utils/test_is_builtin.c \
			tests/utils/test_create_newenv.c \
			tests/utils/test_add_newval_to_env.c \
			tests/utils/test_has_slash.c \
			tests/utils/test_add_str_to_list.c \
			tests/utils/test_split_line.c \
			tests/parser/test_parser.c \
			tests/execute/test_connect_pipeline.c \
			tests/execute/test_do_redirection.c \
			tests/execute/test_get_cmd_frompath.c \
			tests/execute/test_join_path.c \
			tests/execute/test_reconnect_stdfd.c \
			tests/execute/test_execute_sequential.c \
			tests/execute/test_execute_parallel.c \
			tests/execute/test_start_commands.c \
			tests/execute/test_read_command.c \
			tests/builtin/test_execute_env.c \
			tests/builtin/test_execute_unset.c \
			tests/builtin/test_execute_pwd.c \
			tests/builtin/test_execute_echo.c \
			tests/builtin/test_execute_cd.c \
			tests/tokenizer/test_tokenize.c


SRCDIRS = $(dir $(SRCFILE))
OBJDIR = ./obj
BINDIRS = $(addprefix $(OBJDIR)/, $(SRCDIRS))
OBJECTS = $(addprefix $(OBJDIR)/, $(SRCFILE:.c=.o))
TEST = $(notdir $(basename $(SRCFILE)))

all: $(NAME)

$(LIBFT):
	$(MAKE) bonus -C ./libft

$(NAME): $(OBJECTS) $(LIBFT)
	gcc -g $^ $(INCLUDES) -o $@

$(OBJDIR)/%.o: %.c
	@mkdir -p $(BINDIRS)
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(TEST): $(LIBFT)
	gcc -g -fsanitize=address $(filter tests/%/test_$@.c, $(TESTFILE)) tests/print_tcommand.c \
	$(filter-out srcs/main/main.c ,$(SRCFILE)) $(INCLUDES) $^ -o test

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJECTS)
	$(RM) -rf $(OBJDIR)

fclean:
	$(MAKE) fclean -C ./libft
	$(RM) $(OBJECTS) $(NAME)
	$(RM) -rf $(OBJDIR)
	$(RM) -rf test test.dSYM

re: fclean all

.PHONY: all clean fclean re
