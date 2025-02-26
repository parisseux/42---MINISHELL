/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:56:27 by avarrett          #+#    #+#             */
/*   Updated: 2024/10/17 18:21:53 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*element_liste;
	t_list	*the_list;

	if (!lst || !f || !del)
		return (NULL);
	the_list = 0;
	while (lst)
	{
		element_liste = ft_lstnew(f(lst->content));
		if (!element_liste)
		{
			ft_lstclear(&the_list, del);
			return (NULL);
		}
		ft_lstadd_back(&the_list, element_liste);
		lst = lst->next;
	}
	return (the_list);
}
