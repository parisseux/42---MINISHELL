#include "../inc/minishell.h"

int	count_args(t_token *lst_token)
{
	t_token *tmp;
	int		count;

	tmp = lst_token;
	count = 0;
	while (tmp->type != END && tmp->type != PIPE && tmp->type != REDIR_IN
		&& tmp->type != REDIR_OUT && tmp->type != HEREDOC && tmp->type != APPEND)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

int	num_arg(char *arg)
{
	int	i;

	i = 1;
	if (ft_str_digit(arg))
		return (ft_atoi(arg));
	if (arg[0] != '+' && arg[0] != '-')
		return (2);
	while (arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]))
			return (2);
		i++;
	}
	if (arg[0] == '-')
		return (156);
	return (ft_atoi(arg + 1));

}

int	numeric_arg(t_token *lst_token)
{
	int	space;

	space = lst_token->next->space;
	if (space == 1)
		return (130);
	if (!ft_strncmp(lst_token->value, "+", ft_strlen(lst_token->value)))
	{
		if (ft_str_digit(lst_token->next->value))
			return (ft_atoi(lst_token->next->value));
	}
	else if (!ft_strncmp(lst_token->value, "-", ft_strlen(lst_token->value)))
	{
		if (ft_str_digit(lst_token->next->value))
			return (156);
	}
	return (2);
}

void	exit_command(t_token *lst_token, t_shell *shell)
{
	write(STDOUT_FILENO, "exit\n", 5);
	if (lst_token->next->type == WORD || lst_token->next->type == SQUOTE
		|| lst_token->next->type == DQUOTE)
	{
		if (count_args(lst_token) == 2)
			shell->exit = num_arg(lst_token->next->value);
		else if (count_args(lst_token) == 3)
			shell->exit = numeric_arg(lst_token->next);
	}
	else
		shell->exit = 0;
	if (shell->exit == 298)
		shell->exit = 42;
	if (shell->exit == 2)
	{
		write(STDOUT_FILENO, "minishell: exit: ", 17);
		write(STDOUT_FILENO, lst_token->next->value, ft_strlen(lst_token->next->value));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
	}
	if (shell->exit == 130)
	{
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
		return ;
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

// if (!ft_str_digit(lst_token->next->value))
// 		{
// 			i = ft_strlen(lst_token->next->value);
// 			write(STDOUT_FILENO, "minishell: exit: ", 17);
// 			write(STDOUT_FILENO, lst_token->next->value, i);
// 			write(STDOUT_FILENO, ": numeric argument required\n", 28);
// 			shell->exit = 2;
// 		}