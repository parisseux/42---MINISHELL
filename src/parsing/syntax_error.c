#include "minishell.h"

int	check_syntax_error(t_token *lst_token)
{
	if (check_first_last_token(lst_token))
		return (1);
	else if (check_synthax_pipe(lst_token))
		return (1);
	else if (check_synthax_redirection(lst_token))
		return (1);
	return (0);
}

int	check_first_last_token(t_token *lst_token)
{
	t_token	*temp;

	temp = lst_token;
	if (temp->type == PIPE)
	{
		write(STDERR_FILENO, "bash: syntax error near unexpected token `|'\n", 45);
		return (2);
	}
	while (temp->next->type != END)
		temp = temp->next;
	if (temp->type == PIPE)
	{
		write(STDERR_FILENO, "bash: syntax error: unexpected end of file\n", 44);
		return (2);
	}
	else if (temp->type == REDIR_IN || temp->type == REDIR_OUT
		|| temp->type == HEREDOC || temp->type == APPEND)
	{
		write(STDERR_FILENO, "bash: syntax error near unexpected token `newline'\n", 51);
		return (2);
	}
	return (0);
}

int	check_synthax_pipe(t_token *lst_token)
{
	t_token	*temp;

	temp = lst_token;
	while (temp->type != END)
	{
		if (temp->type == PIPE)
		{
			if (temp->next->type == REDIR_IN || temp->next->type == REDIR_OUT
					|| temp->next->type == HEREDOC || temp->next->type == APPEND)
				perror("lala");
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
			perror("bash: syntax error near unexpected token `>'\n");
			return (1);
		}
		else if (temp->type == REDIR_OUT && (temp->next->type == REDIR_IN
				|| temp->next->type == HEREDOC))
		{
			perror("bash: syntax error near unexpected token `<'\n");
			return (1);
		}
		else if (temp->type == HEREDOC && (temp->next->type == REDIR_IN
				|| temp->next->type == APPEND || temp->next->type == REDIR_OUT
				|| temp->next->type == HEREDOC))
		{
			perror("bash: syntax error near unexpected token `<<'\n");
			return (1);
		}
		else if (temp->type == APPEND && (temp->next->type == REDIR_IN
				|| temp->next->type == APPEND || temp->next->type == REDIR_OUT
				|| temp->next->type == HEREDOC))
		{
			perror("bash: syntax error near unexpected token `>>'\n");
			return (1);
		}
		else if ((temp->type == REDIR_IN || temp->type == APPEND
				|| temp->type == HEREDOC) && temp->next->type == PIPE)
		{
			perror("bash: syntax error near unexpected token `|'\n");
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}
