#include "../inc/minishell.h"

//corriger pour gerer correcter les STDOUT
//dup2 allow to redirect the outsput to the file associated to fd
void	env_command(t_shell *shell, t_token *lst_token, int fd_out)
{
	int i;
	int saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	if (fd_out != -1)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	i = 0;
	if (lst_token->next->type == END || lst_token->next->type == PIPE 
		|| lst_token->next->type == APPEND || lst_token->next->type == REDIR_OUT)
	{
		while (shell->var_env[i])
		{
			write(STDOUT_FILENO, shell->var_env[i], ft_strlen(shell->var_env[i]));
			write(STDOUT_FILENO, "\n", 1);
			i++;
		}
	}
	else
	{
		write(STDOUT_FILENO,"env ", 4);
		write(STDOUT_FILENO,lst_token->next->value, ft_strlen(lst_token->next->value));
		write(STDOUT_FILENO, ": No such file or directory\n", 28);
	}
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}
