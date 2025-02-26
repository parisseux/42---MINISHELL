/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:32:49 by avarrett          #+#    #+#             */
/*   Updated: 2024/10/17 18:00:22 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*liste;

	if (lst)
	{
		while (*lst)
		{
			liste = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = liste;
		}
	}		
}
