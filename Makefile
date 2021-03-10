CFLAGS = -Wall -Wextra -Werror
NAME = minishell

SRCFILE =	srcs/utils/create_new_tcommand.c \
			srcs/utils/free_commandslist.c

TESTFILE =	tests/utils/test_create_new_tcommand.c \
			tests/utils/test_free_commandslist.c

OBJDIR = ./obj
OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(SRCFILE:.c=.o)))

TESTCCORE = srcs/utils/create_new_tcommand.c \
			tests/print_tcommand.c

TEST = $(notdir $(basename $(TESTFILE)))

all: $(NAME)

libft:
	$(MAKE) bonus -C ./libft

$(NAME): libft $(OBJECTS)
	gcc -g $(SRCFILE) -I./includes -I./libft -L./libft -lft -o cub3D

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@ -I./includes

$(TEST): libft
	gcc -g $(wildcard tests/*/$(addsuffix .c,$@)) \
	$(wildcard srcs/*/$(addsuffix .c,$(subst test_,,$@))) \
	$(TESTCCORE) -I./includes -I. -L./libft -lft -o test

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJECTS)

fclean:
	$(MAKE) fclean -C ./libft
	$(RM) $(OBJECTS) $(NAME)

re: fclean all

.PHONY: all clean fclean re libft minilibx