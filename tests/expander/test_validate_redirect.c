#include "minishell.h"

int main(void)
{
	t_command *cmd;

	cmd = create_new_tcommand();
	cmd->redirect_out = ft_split(">,$INVALID", ',');
	if (validate_redirect(cmd))
		puts("success");
	ft_free_split(cmd->redirect_out);

	cmd->redirect_out = ft_split(">,$A+100", ',');
	if (validate_redirect(cmd))
		puts("success");
	ft_free_split(cmd->redirect_out);

	cmd->redirect_out = ft_split(">,test,>,$A", ',');
	if (validate_redirect(cmd))
		puts("success");
	ft_free_split(cmd->redirect_out);

	cmd->redirect_out = ft_split(">,$A,>>,$INVALID\"aa\"", ',');
	if (validate_redirect(cmd))
		puts("success");
	ft_free_split(cmd->redirect_out);

	cmd->redirect_out = ft_split(">,'$A',>>,test", ',');
	if (validate_redirect(cmd))
		puts("success");
	ft_free_split(cmd->redirect_out);

	cmd->redirect_out = ft_split(">,$A,>>,$INVALIDaa", ',');
	if (validate_redirect(cmd))
		puts("success");
	//ft_free_split(cmd->redirect_out);

	free_commandslist(&cmd);
	return (0);
}