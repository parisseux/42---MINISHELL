#include "../inc/minishell.h"

t_token	*extract_in(char **input)
{
	t_token	*new_token;

	(*input)++;
	if (**input == '<')
	{
		new_token = create_token("<<", HEREDOC);
		(*input)++;
	}
	else
		new_token = create_token("<", REDIR_IN);
	return (new_token);
}

t_token	*extract_out(char **input)
{
	t_token	*new_token;

	(*input)++;
	if (**input == '>')
	{
		new_token = create_token(">>", APPEND);
		(*input)++;
	}
	else
		new_token = create_token(">", REDIR_OUT);
	return (new_token);
}