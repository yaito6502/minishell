NAME = minishell

CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes -I.

LIBFT = ./libft/libft.a

SRCFILE =	srcs/main/main.c \
			srcs/main/read_line.c \
			srcs/main/back_line.c \
			srcs/main/get_signal_in_read_line.c \
			srcs/main/terminal_setting.c \
			srcs/main/termcap_setting.c \
			srcs/utils/create_new_tcommand.c \
			srcs/utils/free_commandslist.c \
			srcs/utils/is_builtin.c \
			srcs/utils/create_newenv.c \
			srcs/utils/add_newval_to_env.c \
			srcs/utils/has_slash.c \
			srcs/utils/add_str_to_list.c \
			srcs/utils/split_line.c \
			srcs/utils/validate_envkey.c \
			srcs/utils/update_env.c \
			srcs/utils/print_sorted_env.c \
			srcs/utils/wrap_exit.c \
			srcs/utils/get_escapestr.c \
			srcs/utils/add_path.c \
			srcs/utils/update_shlvl.c \
			srcs/parser/parser.c \
			srcs/parser/parser_utils.c \
			srcs/expander/expander.c \
			srcs/expander/is_empty_env.c \
			srcs/expander/expand_tilde.c \
			srcs/expander/expand_envval.c \
			srcs/expander/get_envname.c \
			srcs/expander/expand_utils.c \
			srcs/expander/validate_redirect.c \
			srcs/execute/connect_pipeline.c \
			srcs/execute/do_redirection.c \
			srcs/execute/error_redirect.c \
			srcs/execute/get_cmd_frompath.c \
			srcs/execute/create_newpath.c \
			srcs/execute/reconnect_stdfd.c \
			srcs/execute/execute_sequential.c \
			srcs/execute/execute_parallel.c \
			srcs/execute/start_commands.c \
			srcs/execute/read_command.c \
			srcs/execute/error_execute.c \
			srcs/execute/store_exitstatus.c \
			srcs/main/get_signal_in_execute.c \
			srcs/builtin/execute_builtin.c \
			srcs/builtin/execute_env.c \
			srcs/builtin/execute_unset.c \
			srcs/builtin/execute_pwd.c \
			srcs/builtin/execute_echo.c \
			srcs/builtin/execute_export.c \
			srcs/builtin/execute_cd.c \
			srcs/builtin/execute_exit.c \
			srcs/tokenizer/tokenize.c \
			srcs/tokenizer/validate_line.c \
			srcs/tokenizer/validate_quote.c \
			srcs/history/history.c \
			srcs/history/display_history.c \
			srcs/history/update_history.c \
			srcs/history/get_cursor_position.c


TESTFILE =	tests/print_tcommand.c \
			tests/main/test_read_line.c \
			tests/main/test_termcap_setting.c \
			tests/utils/test_create_new_tcommand.c \
			tests/utils/test_free_commandslist.c \
			tests/utils/test_is_builtin.c \
			tests/utils/test_create_newenv.c \
			tests/utils/test_add_newval_to_env.c \
			tests/utils/test_has_slash.c \
			tests/utils/test_add_str_to_list.c \
			tests/utils/test_split_line.c \
			tests/utils/test_validate_envkey.c \
			tests/utils/test_update_env.c \
			tests/utils/test_get_escapestr.c \
			tests/parser/test_parser.c \
			tests/expander/test_expander.c \
			tests/expander/test_expand_envval.c \
			tests/expander/test_validate_redirect.c \
			tests/execute/test_connect_pipeline.c \
			tests/execute/test_do_redirection.c \
			tests/execute/test_get_cmd_frompath.c \
			tests/execute/test_create_newpath.c \
			tests/execute/test_reconnect_stdfd.c \
			tests/execute/test_execute_sequential.c \
			tests/execute/test_execute_parallel.c \
			tests/execute/test_start_commands.c \
			tests/execute/test_read_command.c \
			tests/execute/test_store_exitstatus.c \
			tests/builtin/test_execute_env.c \
			tests/builtin/test_execute_unset.c \
			tests/builtin/test_execute_pwd.c \
			tests/builtin/test_execute_echo.c \
			tests/builtin/test_execute_export.c \
			tests/builtin/test_execute_cd.c \
			tests/builtin/test_execute_exit.c \
			tests/tokenizer/test_tokenize.c \
			tests/tokenizer/test_validate_line.c \
			tests/tokenizer/test_validate_quote.c \
			tests/history/test_history.c


SRCDIRS = $(dir $(SRCFILE))
OBJDIR = ./obj
BINDIRS = $(addprefix $(OBJDIR)/, $(SRCDIRS))
OBJECTS = $(addprefix $(OBJDIR)/, $(SRCFILE:.c=.o))
TEST = $(notdir $(basename $(SRCFILE)))

all: $(NAME)

$(LIBFT):
	$(MAKE) bonus -C ./libft

$(NAME): $(OBJECTS) $(LIBFT)
	gcc -g $(CFLAGS) $^ $(INCLUDES) -ltermcap -o $@

$(OBJDIR)/%.o: %.c
	@mkdir -p $(BINDIRS)
	gcc -g $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TEST): $(OBJECTS) $(LIBFT)
	gcc -g $(filter tests/%/test_$@.c, $(TESTFILE)) tests/print_tcommand.c \
	$(filter-out obj/srcs/main/main.o, $^) $(INCLUDES) -ltermcap -o test

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
