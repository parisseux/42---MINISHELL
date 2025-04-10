#include "../inc/minishell.h"

int	extract_exit_status(int status, t_shell *shell)
{
	if (WIFEXITED(status))
		shell->exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit = 128 + WTERMSIG(status);
	else
		shell->exit = 0;
	if (shell->exit == 0)
		return (0);
	else
		return (1);
}

void	exit_message(t_shell *shell, t_token *exit)
{
	write(STDERR_FILENO, "minishell: exit: numeric argument required\n", 43);
	clean_exit(2, exit, shell->var_env, shell->shell_env);
}

int	start_echo(t_token *lst_token)
{
	if (lst_token->next->type == END)
		write(STDOUT_FILENO, "\n", 1);
	else if (!ft_strncmp(lst_token->next->value, "-n", 2))
		echo_command(lst_token->next->next, 1);
	else
		echo_command(lst_token->next, 0);
	return (1);
}
