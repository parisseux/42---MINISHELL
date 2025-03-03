/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninisse <ninisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:44:03 by pchatagn          #+#    #+#             */
/*   Updated: 2025/03/03 13:06:53 by ninisse          ###   ########.fr       */
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

int	ft_varcmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	while (i < n && (s2[i] || s1[i]))
	{
		if ((unsigned char) s1[i] == (unsigned char) s2[i])
			i++;
		else
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
	}
	if (s1[i] != '=')
		return (1);
	return (0);
}
