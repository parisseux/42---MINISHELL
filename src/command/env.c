#include "../inc/minishell.h"

//exit stauts grace a waitpid

void	env_command(t_shell *shell, t_token *lst_token)
{
	int	i;

	i = 0;
	if (lst_token->next->type == END || lst_token->next->type == PIPE
		|| lst_token->next->type == APPEND
		|| lst_token->next->type == REDIR_OUT)
	{
		while (shell->var_env[i])
		{
			write(STDOUT_FILENO, shell->var_env[i], ft_strlen(shell->var_env[i]));
			write(STDOUT_FILENO, "\n", 1);
			i++;
		}
	}
	else
		printf("env %s: No such file or directory\n", lst_token->next->value);

}
