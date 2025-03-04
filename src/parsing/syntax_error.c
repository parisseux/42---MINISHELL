/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchatagn <pchatagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:43:31 by pchatagn          #+#    #+#             */
/*   Updated: 2025/03/03 17:14:58 by pchatagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_error(t_token *lst_token)
{
	if (check_first_last_token(lst_token))
		return (1);
	// else if (check_synthax_pipe(lst_token))
	// 	return (1);
	else if (check_synthax_redirection(lst_token))
		return (1);
	return (0);
}

int	check_first_last_token(t_token *lst_token)
{
	t_token *temp;

	temp = lst_token;
	if (temp->type == PIPE)
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (1);
	}
	while (temp->next->type != END)
		temp = temp->next;
	if (temp->type == PIPE)
	{
		printf("bash: syntax error: unexpected end of file\n");
		return (1);
	}
	else if (temp->type == REDIR_IN || temp->type == REDIR_OUT
				|| temp->type == HEREDOC || temp->type == APPEND)
	{
		printf("bash: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

//jsp comment gerer ca en vrai pck on doit pas gerer || mais en soit cest pas vrm une erreur

// int	check_synthax_pipe(t_token *lst_token)
// {
// 	t_token *temp;

// 	temp = lst_token;
// 	while (temp->type != END)
// 	{
// 		if (temp->type == PIPE)
// 		{
// 			if (temp->next->type == REDIR_IN || temp->next->type == REDIR_OUT
// 					|| temp->next->type == HEREDOC || temp->next->type == APPEND)
// 				printf("");
// 		}
// 		temp = temp->next;
// 	}
// }

int	check_synthax_redirection(t_token *lst_token)
{
	t_token *temp;

	temp = lst_token;
	while (temp->type != END)
	{
		if (temp->type == REDIR_IN && (temp->next->type == REDIR_OUT
			|| temp->next->type == APPEND))
		{
			printf("bash: syntax error near unexpected token `>'\n");
			return (1);
		}
		else if (temp->type == REDIR_OUT && (temp->next->type == REDIR_IN
			|| temp->next->type == HEREDOC))
		{
			printf("bash: syntax error near unexpected token `<'\n");
			return (1);	
		}
		else if (temp->type == HEREDOC && (temp->next->type == REDIR_IN
			|| temp->next->type == APPEND || temp->next->type == REDIR_OUT
			|| temp->next->type == HEREDOC))
		{
			printf("bash: syntax error near unexpected token `<<'\n");
			return (1);
		}
		else if (temp->type == APPEND && (temp->next->type == REDIR_IN
			|| temp->next->type == APPEND || temp->next->type == REDIR_OUT
			|| temp->next->type == HEREDOC))
		{
			printf("bash: syntax error near unexpected token `>>'\n");
			return (1);
		}
		else if ((temp->type == REDIR_IN || temp->type == APPEND || temp->type == HEREDOC) && temp->next->type == PIPE)
		{
			printf("bash: syntax error near unexpected token `|'\n");
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

