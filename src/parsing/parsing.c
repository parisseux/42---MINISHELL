/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchatagn <pchatagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:26:11 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/01 16:26:12 by pchatagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*parse_s_quote(char **input, t_token *lst_token)
{
	t_token	*token;

	token = extract_s_quote(input);
	if (!token)
	{
		msg_error("unclosed single quote", lst_token);
		return (NULL);
	}
	return (token);
}

t_token	*parse_d_quote(char **input, t_token *lst_token)
{
	t_token	*token;

	token = extract_d_quote(input);
	if (!token)
	{
		msg_error("unclosed double quote", lst_token);
		return (NULL);
	}
	return (token);
}

t_token	*parse_token(char **input, t_token *lst_token)
{
	if (detect_var(*input) && !in_quote('=', *input) && !not_cmd(lst_token))
		return (token_var(input));
	else if (**input == '|')
		return (parse_pipe(input));
	else if (**input == '\'')
		return (parse_s_quote(input, lst_token));
	else if (**input == '"')
		return (parse_d_quote(input, lst_token));
	else if (**input == '/' || (**input == '.' && **input + 1 == '/'))
		return (bin_path(input));
	else if (**input == '>')
		return (extract_out(input));
	else if (**input == '<')
		return (extract_in(input));
	else
		return (ext_word(input));
}

t_token	*tokenisation(char *input)
{
	t_token	*lst_token;
	t_token	*new_token;
	int		space;

	lst_token = NULL;
	while (*input)
	{
		space = skip_space(&input);
		if (*input == '\0')
			break ;
		new_token = parse_token(&input, lst_token);
		if (!new_token)
			return (NULL);
		add_token_to_lst(&lst_token, new_token, space);
	}
	add_token_to_lst(&lst_token, create_token("", END, -1), space);
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
