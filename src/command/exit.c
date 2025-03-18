#include "../inc/minishell.h"

void	exit_command(t_token *lst_token, t_shell *shell)
{
	int	i;

	i = 0;
	write(STDOUT_FILENO, "exit\n", 5);
	if (lst_token->next->type == WORD || lst_token->next->type == SQUOTE
		|| lst_token->next->type == DQUOTE)
	{
		if (!ft_str_digit(lst_token->next->value))
		{
			i = ft_strlen(lst_token->next->value);
			write(STDOUT_FILENO, "minishell: exit: ", 17);
			write(STDOUT_FILENO, lst_token->next->value, i);
			write(STDOUT_FILENO, ": numeric argument required\n", 28);
			shell->exit = 2;
		}
		else
			shell->exit = 0;
	}
	free_token_list(lst_token);
	ft_free_char_tab(shell->var_env);
	exit (shell->exit);
}

int extract_exit_status(int status, t_shell *shell)
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