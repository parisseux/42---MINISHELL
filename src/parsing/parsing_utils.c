/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchatagn <pchatagn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:25:31 by pchatagn          #+#    #+#             */
/*   Updated: 2025/03/03 17:15:17 by pchatagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	skip_space(char **input)
{
	while (**input == ' ' || **input == '\t' || **input == '\v'
			||**input == '\r' ||**input == '\n' || **input == '\f')
		(*input)++;
}

void print_token_list(t_token *lst_token)
{
	t_token *current = lst_token;

	while (current)
	{
		if (current->value != NULL)
		{
			printf("Token: [%s], Type: %d\n", current->value, current->type);
		}
		else
		{
			printf("Token: [NULL] ou Type: NULL \n");
		}
		current = current->next;
	}
}