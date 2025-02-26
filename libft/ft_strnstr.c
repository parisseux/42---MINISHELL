/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ninisse <ninisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:36:31 by gregorykoll       #+#    #+#             */
/*   Updated: 2025/02/05 11:55:25 by ninisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *foin, const char *aiguille, size_t a)
{
	size_t	i;
	size_t	j;
	size_t	complet;

	j = 0;
	i = 0;
	complet = ft_strlen(aiguille);
	if (complet == 0)
		return ((char *)foin);
	while (foin[i] && i < a)
	{
		j = 0;
		while (foin[i + j] == aiguille[j] && (i + j < a))
		{
			if (j == complet)
				return ((char *)&foin[i]);
			j++;
		}
		if (j == complet)
			return ((char *)&foin[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// int main(void)
// {
// 	const char str[80] = "lorem ipsum dolor sit amet";
// 	const char str2[40] = "ipsum";
//     size_t len = 15;
// 	printf("%s", ft_strnstr(str, str2, len));
// 	return (0);
// }