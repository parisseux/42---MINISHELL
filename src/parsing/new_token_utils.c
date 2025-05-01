/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchatagn <pchatagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:25:22 by pchatagn          #+#    #+#             */
/*   Updated: 2025/05/01 16:25:23 by pchatagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
