CFLAGS = -Wall -Wextra -Werror
NAME = minishell

SRCFILE =	srcs/utils/create_new_tcommand.c \
			srcs/utils/free_commandslist.c \
			srcs/utils/is_builtin.c \
			srcs/utils/create_newenv.c \
			srcs/utils/add_newval_to_env.c \
			srcs/execute/connect_pipeline.c \
			srcs/execute/do_redirection.c \
			srcs/execute/get_cmd_frompath.c \
			srcs/execute/execute_sequential.c


TESTFILE =	tests/utils/test_create_new_tcommand.c \
			tests/utils/test_free_commandslist.c \
			tests/utils/test_is_builtin.c \
			tests/utils/test_create_newenv.c \
			tests/utils/add_newval_to_env.c \
			tests/utils/test_add_newval_to_env.c \
			tests/execute/test_connect_pipeline.c \
			test/execute/test_do_redirection.c \
			test/execute/test_get_cmd_frompath.c \
			tests/execute/test_execute_sequential.c \


OBJDIR = ./obj
OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(SRCFILE:.c=.o)))

TESTCORE =	srcs/utils/create_new_tcommand.c \
			srcs/utils/free_commandslist.c \
			srcs/utils/create_newenv.c \
			srcs/utils/is_builtin.c \
			srcs/execute/get_cmd_frompath.c \
			tests/print_tcommand.c


TEST = $(notdir $(basename $(SRCFILE)))

all: $(NAME)

# $(NAME): libft $(OBJECTS)
	# gcc -g $(SRCFILE) -I./includes -I./libft -L./libft -lft -o cub3D

libft:
	$(MAKE) bonus -C ./libft

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@ -I./includes

$(TEST): libft
	gcc -g $(sort $(wildcard tests/*/$(addprefix test_,$(addsuffix .c,$@))) \
	$(wildcard srcs/*/$(addsuffix .c,$@)) \
	$(TESTCORE)) -I./includes -I. -L./libft -lft -o test

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJECTS)

fclean:
	$(MAKE) fclean -C ./libft
	$(RM) $(OBJECTS) $(NAME)

re: fclean all

.PHONY: all clean fclean re libft minilibx