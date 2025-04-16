#include "../inc/minishell.h"

int	is_pipe(t_token *lst_token)
{
	t_token	*temp;
	int		pipe;

	pipe = 0;
	temp = lst_token;
	while (temp->type != END)
	{
		if (temp->type == PIPE)
			pipe++;
		temp = temp->next;
	}
	return (pipe);
}

int	is_def(t_token *lst_token)
{
	t_token	*temp;

	temp = lst_token;
	while (temp->type != END)
	{
		if (temp->type == DEF)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	is_cmd_before_builtin(t_token *builtin, t_token *lst_token)
{
	t_token	*temp;

	temp = lst_token;
	while (temp != builtin && temp->type != END && temp->type != PIPE)
	{
		if (temp->type == REDIR_IN || temp->type == REDIR_OUT
			|| temp->type == APPEND || temp->type == HEREDOC)
		{
			temp = temp->next;
			if (temp)
				temp = temp->next;
		}
		else if (temp->type == WORD || temp->type == SQUOTE
			|| temp->type == DQUOTE
			|| temp->type == DEF || temp->type == BIN)
			return (1);
		else
			temp = temp->next;
	}	
	return (0);
}

int	is_builtin(t_token *lst_token)
{
	t_token	*t;

	t = lst_token;
	while (t->type != END && t->type != PIPE)
	{
		if (t->type == WORD && (t->next->space == 1
				|| t->next->type == END || t->next->type == PIPE))
		{
			if (!ft_strncmp(t->value, "echo", 5)
				|| !ft_strncmp(t->value, "cd", 3)
				|| !ft_strncmp(t->value, "pwd", 4)
				|| !ft_strncmp(t->value, "export", 7)
				|| !ft_strncmp(t->value, "unset", 5)
				|| !ft_strncmp(t->value, "env", 4)
				|| !ft_strncmp(t->value, "exit", 6))
			{
				if (is_cmd_before_builtin(t, lst_token) == 0)
					return (1);
			}
		}
		t = t->next;
	}
	return (0);
}

int	is_redir(t_token *lst_token)
{
	t_token	*temp;

	temp = lst_token;
	while (temp->type != END)
	{
		if (temp->type == HEREDOC)
			return (1);
		else if (temp->type == APPEND)
			return (2);
		else if (temp->type == REDIR_IN)
			return (3);
		else if (temp->type == REDIR_OUT)
			return (4);
		temp = temp->next;
	}
	return (0);
}
