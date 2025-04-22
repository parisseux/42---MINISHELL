#include "../inc/minishell.h"

int	print_env(t_shell *shell)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (shell->var_env[i])
	{
		len = ft_strlen(shell->var_env[i]);
		if (len == 0)
			return (0);
		write(STDOUT_FILENO, shell->var_env[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (0);
}

int	env_command(t_shell *shell, t_token *lst)
{
	if (lst->next->type == END || lst->next->type == PIPE
		|| lst->next->type == APPEND || lst->next->type == REDIR_IN
		|| lst->next->type == REDIR_OUT || lst->next->type == HEREDOC)
		return (print_env(shell));
	else
	{
		ft_putstr_fd("env ", 2);
		ft_putstr_fd(lst->next->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	return (1);
}
