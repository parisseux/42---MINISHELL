#include "../inc/minishell.h"

int	minus_exit(char *arg)
{
	int	sign;

	sign = 0;
	if (ft_atoi(arg) > 0)
		sign = -1;
	else
		sign = 1;
	if (ft_atoi(arg) == -1)
		return (255);
	else if ((ft_atoi(arg)) == 3)
		return (3);
	else
	{
		write(1, "pas min", 7);
		return (sign * ft_atoi(arg));
	}
		
}
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

void exit_message(t_shell *shell, t_token *exit)
{
	write(STDERR_FILENO, "minishell: exit: numeric argument required\n", 43);
	clean_exit(2, exit, shell->var_env, shell->shell_env);
}

int	num_arg(char *arg, t_shell *shell, t_token *lst_token)
{
	int	i;

	i = 1;
	if (ft_str_digit(arg))
		return (ft_atoi(arg));
	if (arg[0] != '+' && arg[0] != '-' && !ft_isdigit(arg[0]))
		exit_message(shell, lst_token);
	if (arg[1] == '\0')
		exit_message(shell, lst_token);
	while (arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]))
			exit_message(shell, lst_token);
		i++;
	}
	if (arg[0] == '-')
		return (minus_exit(arg));
	return (ft_atoi(arg));
}

int	arg_ok(char *arg)
{
	int	i;

	i = 1;
	if (ft_str_digit(arg))
		return (1);
	if (arg[0] != '+' && arg[0] != '-' && !ft_isdigit(arg[0]))
		return (0);
	if (arg[1] == '\0')
		return (0);
	while (arg[i] != '\0')
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}



int	numeric_arg(t_token *lst_token, t_shell *shell)
{
	int		space;
	char	*arg1;
	char	*arg2;

	arg2 = lst_token->next->next->value;
	arg1 = lst_token->next->value;
	space = lst_token->next->next->space;
	if (space == 1 && ft_str_digit(arg2))
		exit_message(shell, lst_token);
	if (!ft_strncmp(arg1, "+", ft_strlen(arg1)))
	{
		if (ft_str_digit(arg2))
			return (ft_atoi(arg2));
	}
	else if (!ft_strncmp(arg1, "-", ft_strlen(arg1)))
	{
		if (ft_str_digit(arg2))
			return (minus_exit(arg2));
	}
	exit_message(shell, lst_token);
	return (0);
}

void	exit_command(t_token *exit, t_shell *shell)
{
	write(STDOUT_FILENO, "exit\n", 5);
	if (exit->next->type == END || exit->type == PIPE)
		clean_exit(shell->exit, exit, shell->var_env, shell->shell_env);
	else if (exit->next->next->type == WORD || exit->next->next->type == SQUOTE
		|| exit->next->next->type == DQUOTE)
	{
		if (exit->next->next->space == 1 && arg_ok(exit->next->value))
		{
			write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
			shell->exit = 1;
			return ;
		}
		else
			shell->exit = numeric_arg(exit, shell);
	}
	else if (exit->type == WORD || exit->type == SQUOTE || exit->type == DQUOTE)
		shell->exit = num_arg(exit->next->value, shell, exit);
	else
		shell->exit = 0;

	if (shell->exit > 255 || shell->exit < 0)
		shell->exit &= 255;
	clean_exit(shell->exit, exit, shell->var_env, shell->shell_env);
}
