/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:44:03 by pchatagn          #+#    #+#             */
/*   Updated: 2025/02/25 12:20:15 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_token_list(t_token *lst_token)
{
	t_token	*tmp;

	while (lst_token)
	{
		tmp = lst_token;
		lst_token = lst_token->next;
		free(tmp->value);
		free(tmp);
	}
}

void	msg_error(char *msg, t_token *lst_token)
{
	printf("Error: %s\n", msg);
	free_token_list(lst_token);
}

void	ft_free_char_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
