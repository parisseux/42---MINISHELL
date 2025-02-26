/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:23:51 by pchatagn          #+#    #+#             */
/*   Updated: 2025/02/25 15:57:33 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*tokenisation(char *input)
{
	t_token	*lst_token;
	t_token	*new_token;

	lst_token = NULL;
	while (*input)
	{
		skip_space(&input);
		if (*input == '\0')
			break ;
		if (*input == '|')
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
		else if (*input == '>')
			new_token = extract_out(&input);
		else if (*input == '<')
			new_token = extract_in(&input);
		else
			new_token = ext_word(&input);
		printf("new_token %s\n", new_token->value);
		add_token_to_lst(&lst_token, new_token);
	}
	new_token = create_token("", END);
	add_token_to_lst(&lst_token, new_token);
	return (lst_token);
}

void	add_token_to_lst(t_token **lst_token, t_token *new_token)
{
	t_token	*temp;

	if (!new_token)
		return ;
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
