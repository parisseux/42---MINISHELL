/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:25:31 by pchatagn          #+#    #+#             */
/*   Updated: 2025/02/25 15:57:28 by avarrett         ###   ########.fr       */
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