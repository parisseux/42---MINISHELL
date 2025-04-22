/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarrett <avarrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:57:48 by avarrett          #+#    #+#             */
/*   Updated: 2025/04/22 15:46:40 by avarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	desti;
	size_t	source;
	int		i;
	int		result;

	desti = ft_strlen(dest);
	source = ft_strlen(src);
	i = 0;
	result = 0;
	if (desti >= size)
		result = size + source;
	else
		result = source + desti;
	while (src[i] && (desti + 1) < size)
	{
		dest[desti] = src[i];
		i++;
		desti++;
	}
	dest[desti] = '\0';
	return (result);
}

// #include <stdio.h>
// int main(void)
// {
// 	char first[] = "ana";
// 	char deux[] = "ana";
// 	size_t taille;
// 	taille = ft_strlcat(first, deux, 8);
// 	printf("%zu", taille);
// 	return (0);
// }