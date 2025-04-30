#include "../inc/minishell.h"

t_token	*extract_in(char **input)
{
	t_token	*new_token;

	(*input)++;
	if (**input == '<')
	{
		new_token = create_token("<<", HEREDOC, -1);
		(*input)++;
	}
	else
		new_token = create_token("<", REDIR_IN, -1);
	return (new_token);
}

t_token	*extract_out(char **input)
{
	t_token	*new_token;

	(*input)++;
	if (**input == '>')
	{
		new_token = create_token(">>", APPEND, -1);
		(*input)++;
	}
	else
		new_token = create_token(">", REDIR_OUT, -1);
	return (new_token);
}
