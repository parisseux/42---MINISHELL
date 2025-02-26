/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:19:16 by avarrett          #+#    #+#             */
/*   Updated: 2024/10/17 18:22:06 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*liste;

	liste = malloc(sizeof(t_list));
	if (!liste)
		return (NULL);
	liste->content = content;
	liste->next = NULL;
	return (liste);
}

// #include <stdio.h>
// int	main(void)
// {
//     // Créer un contenu pour le nouvel élément de la liste
//     char *content = "Hello, world!";
//     // Créer un nouvel élément de la liste avec ce contenu
//     t_list *new_elem = ft_lstnew(content);
//     // Vérifier si l'allocation et la création se sont bien passées
//     if (new_elem == NULL)
//     {
//         printf("Échec de la création de l'élément de la liste.\n");
//         return (1);
//     }
//     // Afficher le contenu de l'élément pour vérifier
//     printf("Contenu de l'élément : %s\n", (char *)new_elem->content);
//     // Libérer la mémoire allouée
//     free(new_elem);
//     return (0);
// }
