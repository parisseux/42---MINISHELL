#include "minishell.h"

int	check_first_last_token(t_token *lst_token)
{
	t_token	*temp;

	temp = lst_token;
	if (temp->type == PIPE)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	while (temp->next->type != END)
		temp = temp->next;
	if (temp->type == PIPE)
	{
		ft_putstr_fd("bash: syntax error: unexpected end of file\n", 2);
		return (1);
	}
	else if (temp->type == REDIR_IN || temp->type == REDIR_OUT
		|| temp->type == HEREDOC || temp->type == APPEND)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
		return (1);
	}
	return (0);
}

int	check_synthax_pipe(t_token *lst_token)
{
	t_token	*temp;

	temp = lst_token;
	while (temp->type != END)
	{
		if (temp->type == PIPE && (temp->next->type == PIPE))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
			return (1);
		}
		else if (temp->type == REDIR_OUT && (temp->next->type == REDIR_IN
				|| temp->next->type == HEREDOC))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `<'\n", 2);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	check_synthax_redirection(t_token *lst_token)
{
	t_token	*temp;

	temp = lst_token;
	while (temp->type != END)
	{
		if (temp->type == REDIR_IN && (temp->next->type == REDIR_OUT
				|| temp->next->type == APPEND))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `>'\n", 2);
			return (1);
		}
		else if ((temp->type == REDIR_IN || temp->type == APPEND
				|| temp->type == HEREDOC || temp->type == REDIR_OUT)
			&& temp->next->type == PIPE)
		{
			ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	check_synthax_redirection2(t_token *lst_token)
{
	t_token	*temp;

	temp = lst_token;
	while (temp->type != END)
	{
		if (temp->type == APPEND && (temp->next->type == REDIR_IN
				|| temp->next->type == APPEND || temp->next->type == REDIR_OUT
				|| temp->next->type == HEREDOC))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `>>'\n", 2);
			return (1);
		}
		else if (temp->type == HEREDOC && (temp->next->type == REDIR_IN
				|| temp->next->type == APPEND || temp->next->type == REDIR_OUT
				|| temp->next->type == HEREDOC))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `<<'\n", 2);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	check_syntax_error(t_token *lst_token)
{
	if (check_first_last_token(lst_token))
		return (1);
	else if (check_synthax_pipe(lst_token))
		return (1);
	else if (check_synthax_redirection(lst_token))
		return (1);
	else if (check_synthax_redirection2(lst_token))
		return (1);
	return (0);
}
