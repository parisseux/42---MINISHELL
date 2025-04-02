#include "../inc/minishell.h"

// a modifier --> write au lieu de printf comme exemple de pwd, env
// introduier fd_out avec utilisation de dup() et dup2 comme pour pwd, env
//probleme lie a linux??

//minishell$ echo<<file ->pas bon retour
//exit status grace a waitpid

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
