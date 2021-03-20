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
			srcs/utils/add_str_to_list.c \
			srcs/execute/connect_pipeline.c \
			srcs/execute/do_redirection.c \
			srcs/execute/get_cmd_frompath.c \
			srcs/execute/execute_sequential.c \
			srcs/execute/parser.c \
			srcs/execute/parser_utils.c



TESTFILE =	tests/utils/test_create_new_tcommand.c \
			tests/utils/test_free_commandslist.c \
			tests/utils/test_is_builtin.c \
			tests/utils/test_create_newenv.c \
			tests/utils/add_newval_to_env.c \
			tests/utils/test_add_newval_to_env.c \
			tests/utils/test_add_str_to_list.c \
			test/execute/test_get_cmd_frompath.c \
			tests/execute/test_connect_pipeline.c \
			test/execute/test_do_redirection.c \
			test/execute/test_get_cmd_frompath.c \
			tests/execute/test_execute_sequential.c \
			test/execute/test_parser.c


SRCDIRS = $(dir $(SRCFILE))
OBJDIR = ./obj
BINDIRS = $(addprefix $(OBJDIR)/, $(SRCDIRS))
OBJECTS = $(addprefix $(OBJDIR)/, $(SRCFILE:.c=.o))

TESTCORE =	srcs/utils/create_new_tcommand.c \
			srcs/utils/free_commandslist.c \
			srcs/utils/create_newenv.c \
			srcs/utils/is_builtin.c \
			srcs/utils/add_str_to_list.c \
			srcs/execute/get_cmd_frompath.c \
			srcs/execute/parser_utils.c \
			tests/print_tcommand.c


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
	gcc -g $(sort $(wildcard tests/*/$(addprefix test_,$(addsuffix .c,$@))) \
	$(wildcard srcs/*/$(addsuffix .c,$@)) \
	$(TESTCORE)) $(INCLUDES) $^ -o test

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJECTS)
	$(RM) -rf $(OBJDIR)

fclean:
	$(MAKE) fclean -C ./libft
	$(RM) $(OBJECTS) $(NAME)
	$(RM) -rf $(OBJDIR)

re: fclean all

.PHONY: all clean fclean re
