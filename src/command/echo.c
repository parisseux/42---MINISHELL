#include "../inc/minishell.h"

int	start_echo(t_token *lst_token)
{
	if (lst_token->next->type == END)
		write(STDOUT_FILENO, "\n", 1);
	while (1)
	{
		if (lst_token->type == REDIR_IN || lst_token->type == REDIR_OUT
			|| lst_token->type == APPEND || lst_token->type == HEREDOC)
			lst_token = lst_token->next->next;
		else
			break ;
	}
	echo_command(lst_token->next);
	return (0);
}

int	is_valid_n_flag(char *line)
{
	int	i;

	i = 1;
	if (!line || line[0] != '-')
		return (0);
	while (line[i] == 'n')
		i++;
	if (line[i] != '\0')
		return (0);
	return (1);
}

void	write_echo(t_token *lst)
{
	if (!lst->value)
		return ;
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
			n_flag = 1;
		else if (lst->value && *lst->value)
		{
			stop_skip = 1;
			write_echo(lst);
		}
		lst = lst->next;
	}
	if (n_flag == 0)
		write(STDOUT_FILENO, "\n", 1);
}
