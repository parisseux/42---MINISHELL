#include "../inc/minishell.h"

int start_echo(t_token *lst_token)
{
	if (lst_token->next->type == END)
		write(STDOUT_FILENO, "\n", 1);
	else if (!ft_strncmp(lst_token->next->value, "-n", 2))
		echo_command(lst_token->next->next, 1);
	else
		echo_command(lst_token->next, 0);
	return (1);
}
void	echo_command(t_token *lst_token, int n_flag)
{
	char	*line;
	int		type;

	while (lst_token->type != END && lst_token->type != PIPE)
	{
		if (lst_token->type == REDIR_IN || lst_token->type == REDIR_OUT
			|| lst_token->type == HEREDOC || lst_token->type == APPEND)
			lst_token = lst_token->next->next;
		else
		{
			line = lst_token->value;
			type = lst_token->type;
			if (*line)
			{
				if (type == SQUOTE)
					echo_single_quote(&line);
				else if (type == DQUOTE)
					echo_double_quote(&line);
				else
					echo_no_quote(&line);
				if (lst_token->next->space == 1 && lst_token->next->type != END
					&& lst_token->next->type != PIPE)
					write(STDOUT_FILENO, " ", 1);
			}
			lst_token = lst_token->next;
		}
	}
	if (n_flag == 0)
		write(STDOUT_FILENO, "\n", 1);
}

void	echo_single_quote(char **line)
{
	write (STDOUT_FILENO, *line, ft_strlen(*line));
}

void	echo_double_quote(char **line)
{
	write(STDOUT_FILENO, *line, ft_strlen(*line));
}

void	echo_no_quote(char **line)
{
	write(STDOUT_FILENO, *line, ft_strlen(*line));
}

int	echo_check_n_flag(char **line)
{
	int	n_flag;

	n_flag = 0;
	while (**line == '-' && *((*line) + 1) == 'n')
	{
		(*line) += 2;
		n_flag = 1;
	}
	return (n_flag);
}
