#include "minishell.h"

int main(void)
{
	t_history *history;
	t_history *h_ptr;
	char *line;

	history = NULL;
	history = add_history(history, "test string1");
	history = add_history(history, "test string2");
	history = add_history(history, "test string3");
	h_ptr = history;
	printf("%s\n", history->line);
	history = history->next;
	printf("%s\n", history->line);
	history = history->next;
	printf("%s\n", history->line);
	history = history->prev;
	printf("%s\n", history->line);
	history = history->prev;
	printf("%s\n", history->line);
	free_history(h_ptr);
	return (0);
}
