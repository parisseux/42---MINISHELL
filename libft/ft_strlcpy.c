/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:39:51 by avarrett          #+#    #+#             */
/*   Updated: 2025/04/23 16:37:05 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t	ft_strlcpy(char *dest, const char *src, size_t size)
// {
//     size_t	i;

//     i = ft_strlen(src);
//     if (size > 0)
//     {
//         if (i + 1 < size)
//             ft_memcpy(dest, src, i + 1); // Copie toute la chaîne avec '\0'
//         else
//         {
//             ft_memcpy(dest, src, size - 1); // Copie partielle
//             dest[size - 1] = '\0';         // Ajoute le '\0'
//         }
//     }
//     return (i);
// }

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = ft_strlen(src);
	if (i + 1 < size)
		ft_memcpy(dest, src, i + 1);
	else if (size != 0)
	{
		ft_memcpy(dest, src, size - 1);
		dest[size - 1] = '\0';
	}
	return (i);
}

// #include <stdio.h>
// int main(void)
// {
// 	char b[] = "anabanana";
// 	char *a;

// 	a = malloc(9);
// 	printf("%zu", ft_strlcpy(a, b, 10));
// 	printf("\n%s", a);
// }