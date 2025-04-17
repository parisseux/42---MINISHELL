#include "../inc/minishell.h"

int	start_echo(t_token *lst_token)
{
	if (lst_token->next->type == END)
		write(STDOUT_FILENO, "\n", 1);
	else
		echo_command(lst_token->next);
	return (0);
}

int	is_valid_n_flag(char *line)
{
	if (!line || line[0] != '-')
		return (0);
	if (line[1] != 'n')
		return (0);
	if (line[2] != '\0')
		return (0);
	return (1);
}

void	write_echo(t_token *lst)
{
	write(STDOUT_FILENO, lst->value, ft_strlen(lst->value));
	if (lst->next->space == 1 && lst->next->type != END
		&& lst->next->type != PIPE)
		write(STDOUT_FILENO, " ", 1);
}

void	echo_command(t_token *lst)
{
	int	n_flag;
	int	stop_skip;

	n_flag = 0;
	stop_skip = 0;
	while (lst->type != END && lst->type != PIPE)
	{
		if (lst->type == REDIR_IN || lst->type == REDIR_OUT
			|| lst->type == HEREDOC || lst->type == APPEND)
			lst = lst->next;
		else if (is_valid_n_flag(lst->value) && stop_skip == 0)
		{
			n_flag = 1;
		}
		else if (*lst->value)
		{
			stop_skip = 1;
			write_echo(lst);
		}
		lst = lst->next;
	}
	if (n_flag == 0)
		write(STDOUT_FILENO, "\n", 1);
}
