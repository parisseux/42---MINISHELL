#include "../inc/minishell.h"

int	count_args(t_token *lst_token)
{
	t_token	*tmp;
	int		count;

	tmp = lst_token;
	count = 0;
	while (tmp->type != END && tmp->type != PIPE && tmp->type != REDIR_IN
		&& tmp->type != REDIR_OUT && tmp->type != HEREDOC
		&& tmp->type != APPEND)
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

int	arg_ok(char *arg)
{
	int	i;

	i = 1;
	if (ft_str_digit(arg))
		return (1);
	if (arg[0] != '+' && arg[0] != '-' && !ft_isdigit(arg[0]))
		return (0);
	while (arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	numeric_arg(t_token *lst_token)
{
	int	space;

	space = lst_token->next->space;
	if (space == 1 && ft_str_digit(lst_token->next->value))
		return (2);
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

int	exit_command(t_token *exit, t_shell *shell)
{
	write(STDOUT_FILENO, "exit\n", 5);
	if (exit->next->type == WORD || exit->next->type == SQUOTE
		|| exit->next->type == DQUOTE)
	{
		if (exit->next->space == 1 && arg_ok(exit->value))
		{
			write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
			shell->exit = 1;
			return (1);
		}
		else
			shell->exit = numeric_arg(exit);
	}
	else if (exit->type == WORD || exit->type == SQUOTE || exit->type == DQUOTE)
		shell->exit = num_arg(exit->value);
	else
		shell->exit = 0;
	if (shell->exit > 255)
		shell->exit &= 255;
	if (shell->exit == 2)
	{
		write(STDERR_FILENO, "minishell: exit: ", 17);
		write(STDERR_FILENO, exit->value, ft_strlen(exit->value));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
	}
	clean_exit(shell->exit, exit, shell->var_env, shell->shell_env);
	return (1);
}
