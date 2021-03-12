CFLAGS = -Wall -Wextra -Werror
NAME = minishell

SRCFILE =	srcs/utils/create_new_tcommand.c \
			srcs/utils/free_commandslist.c \
			srcs/utils/is_builtin.c \
			srcs/utils/create_newenv.c \
			srcs/utils/add_newval_to_env.c \
			srcs/execute/connect_pipeline.c

TESTFILE =	tests/utils/test_create_new_tcommand.c \
			tests/utils/test_free_commandslist.c \
			tests/utils/test_is_builtin.c \
			tests/utils/test_create_newenv.c \
			tests/utils/test_add_newval_to_env.c \
			tests/execute/test_connect_pipeline.c


OBJDIR = ./obj
OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(SRCFILE:.c=.o)))

TESTCORE = srcs/utils/create_new_tcommand.c \
			tests/print_tcommand.c

TEST = $(notdir $(basename $(SRCFILE)))

all: $(NAME)

libft:
	$(MAKE) bonus -C ./libft

# $(NAME): libft $(OBJECTS)
	# gcc -g $(SRCFILE) -I./includes -I./libft -L./libft -lft -o cub3D

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@ -I./includes

$(TEST): libft
	gcc -g $(wildcard tests/*/$(addprefix test_,$(addsuffix .c,$@))) \
	$(wildcard srcs/*/$(addsuffix .c,$@)) \
	$(TESTCORE) -I./includes -I. -L./libft -lft -o test

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJECTS)

fclean:
	$(MAKE) fclean -C ./libft
	$(RM) $(OBJECTS) $(NAME)

re: fclean all

.PHONY: all clean fclean re libft minilibx