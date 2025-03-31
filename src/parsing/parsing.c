#include "../inc/minishell.h"

t_token	*tokenisation(char *input)
{
	t_token	*lst_token;
	t_token	*new_token;
	int		space;

	lst_token = NULL;
	while (*input)
	{
		space = 0;
		if (skip_space(&input))
			space = 1;
		if (*input == '\0')
			break ;
		if (detect_var(input) && !in_quote('=', input) && !not_cmd(lst_token))
			new_token = token_var(&input);
		else if (*input == '|')
		{
			new_token = create_token("|", PIPE);
			input++;
		}
		else if (*input == '\'')
		{
			new_token = extract_s_quote(&input);
			if (!new_token)
			{
				msg_error("unclosed single quote", lst_token);
				return (NULL);
			}
		}	
		else if (*input == '"')
		{
			new_token = extract_d_quote(&input);
			if (!new_token)
			{
				msg_error("unclosed double quote", lst_token);
				return (NULL);
			}
		}
		else if (*input == '/')
			new_token = bin_path(&input);	
		else if (*input == '>')
			new_token = extract_out(&input);
		else if (*input == '<')
			new_token = extract_in(&input);
		else
			new_token = ext_word(&input);
		add_token_to_lst(&lst_token, new_token, space);
	}
	new_token = create_token("", END);
	add_token_to_lst(&lst_token, new_token, space);
	print_token_list(lst_token);
	return (lst_token);
}

void	add_token_to_lst(t_token **lst_token, t_token *new_token, int space)
{
	t_token	*temp;

	if (!new_token)
		return ;
	new_token->space = space;
	if (!*lst_token)
	{
		*lst_token = new_token;
		return ;
	}
	else
	{
		temp = *lst_token;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}
